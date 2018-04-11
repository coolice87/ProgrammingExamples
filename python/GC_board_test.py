# -*- coding: utf-8 -*- 

#---------------------------------------------------------------------
#Name:   单板测试程序
#Author:    heliangbin
#Created:   2017/03/31
#Licence:   
#---------------------------------------------------------------------

#import kinds of lib
import wx
import struct
import socket
import threading

sizerspacer=(40, -1)
ststsizerspacer=(sizerspacer[0]*2, -1)
HOST = '192.168.1.123'
PORT = 16384

#################### set the file filter ##############################
savewildcard = "tex files (*.txt)|*.txt|" \
                "log file (*.log)|*.log|"\
				"Python source (*.py; *.pyc)|*.py;*.pyc|"\
				"All files (*.*)|*.*"

#测试内容
#测试产品型号
devItems = [ u"IVS-FDXXX", u"IVS-FRXXX" ]
#后面数字为水平便宜,为了对齐
testItems = ((u"网络测试:",175), 
             (u"RTC测试:",175), 
             (u"LED测试:",175), 
             (u"复位测试:",175),
             (u"HDMI测试:",165),
             (u"音频测试:",175),
             (u"sate测试:",175),
             (u"USB测试:",175),
             (u"SD卡测试:",175),
             (u"WDG测试:", 175)) 
testItemsEnum = {'none':0, 'network':1, 'rtc':2, 'led':3, 'reset':4, 'hdmi':5, 'audio':6, 'sata':7, 'usb':8, 'sd':9, 'wdg':32}
#失败原因
reasonEnum = (u"网线异常 or IP异常 or PHY异常", u"晶振异常", u"三极管异常 or 未控制", u"未按复位键", u"接口不良", u"接口不良", u"不支持", u"不支持", u"不支持", u"flash异常")

#客户端握手
cltStartCmd = (0x55, 0x55, 0xAA, 0xAA)
#设备握手回应
devReplyCmd= (0xAA, 0xAA, 0x55, 0x55)

#客户端请求前缀
cltRequest = (0x7D, 0x7B)
#客户端确认回复
cltReply = (0x7D, 0x7C)

#设备端回应前缀
devReply = (0x7D, 0x7D)
#设备端请求前缀
devRequst = (0x7D, 0x7E)

#设备回应非法命令
devInvalidCmd = (0x7D, 0x7F, 0x00, 0x00)

######################### class and function #########################
#数据转化为字符串
def dataPack(data):
    g_contents.AppendText('send: ')
    str = ''
    for i in range(0, len(data)):
        g_contents.AppendText(hex(data[i])+' ')
        str = str + struct.pack("B", data[i])
    g_contents.AppendText('\n')
    return str

#字符串转化为数据
def dataUnpack(str):
    g_contents.AppendText('receive: ')
    data = []
    for i in range(0, len(str)):
        data.append(struct.unpack("B", str[i])[0])
        g_contents.AppendText(hex(data[i])+' ')
    g_contents.AppendText('\n')
    return data

#创建线程处理socket
class socketThread(threading.Thread):
    def __init__(self, window, ip):
        threading.Thread.__init__(self)
        self.window = window
        self.status = 0
        if ip:
            HOST = ip
        else:
            HOST = '192.168.1.123'
        print HOST
        
        self.sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.sk.settimeout(3)
            self.sk.connect((HOST, PORT))
            self._running = True
        except Exception, e:
            print 'error', e
            self.sk.close()
            self._running = False

    def socketIsOk(self):
        return self._running
    
    def stop(self):
        self._running = False
        self.status = 0
        
    def run(self):
        self.socketClient()
    
    #建立客户端socket
    def socketClient(self):
        self.status = 0
        self.sk.sendall(dataPack(cltStartCmd))
        while self._running:
            try:
                buf = self.sk.recv(1024)
                data = dataUnpack(buf)
                if len(data):
                    self.dealSocket(data)
            except socket.timeout:
                print 'timeout'
                continue
        
        self.sk.close()
    
    #客户端测试请求
    def cltTestRequest(self, testItem):
        senddata = []
        senddata.append(cltRequest[0])
        senddata.append(cltRequest[1])
        senddata.append(testItem)
        senddata.append(0x00)
        self.sk.sendall(dataPack(senddata))
        
    #socket数据处理
    def dealSocket(self, data):
        senddata = []
        if data[0]==devReplyCmd[0] and data[1]==devReplyCmd[1] and data[2]==devReplyCmd[2] and data[3]==devReplyCmd[3]:
            g_contents.AppendText('test network\n')
            self.cltTestRequest(testItemsEnum['network'])
            self.status = testItemsEnum['network']
        #1. network
        if testItemsEnum['network'] == self.status:
            if data[0] == devReply[0] and data[1]==devReply[1] :
                wx.CallAfter(self.window.setItemsText, testItemsEnum['network'], data[2])
                g_contents.AppendText('test RTC\n')
                self.cltTestRequest(testItemsEnum['rtc'])
                self.status = testItemsEnum['rtc']
        #2. rtc
        elif testItemsEnum['rtc'] == self.status:
            if data[0] == devReply[0] and data[1]==devReply[1] :
                wx.CallAfter(self.window.setItemsText, testItemsEnum['rtc'], data[2])
                g_contents.AppendText('test status_led\n')
                self.cltTestRequest(testItemsEnum['led'])
                self.status = testItemsEnum['led']
        #3. led
        elif testItemsEnum['led'] == self.status:
            if data[0]==devRequst[0] and data[1]==devRequst[1]:
                dlg = wx.MessageDialog(None, u"红色|绿色状态灯是否都亮", "MessageDialog", wx.YES_NO | wx.ICON_QUESTION)
                msgdialogStatus = dlg.ShowModal()
                dlg.Destroy()
                senddata.append(cltReply[0])
                senddata.append(cltReply[1])
                if(msgdialogStatus == wx.ID_YES):
                    senddata.append(0x00)
                else:
                    senddata.append(0x01)
                senddata.append(0x00)
                self.sk.sendall(dataPack(senddata))
                
            if data[0] == devReply[0] and data[1]==devReply[1] :
                wx.CallAfter(self.window.setItemsText, testItemsEnum['led'], data[2])
                g_contents.AppendText('test reset key\n')
                self.cltTestRequest(testItemsEnum['reset'])
                self.status = testItemsEnum['reset']
        #4. reset
        elif testItemsEnum['reset'] == self.status:
            if data[0]==devRequst[0] and data[1]==devRequst[1]:
                dlg = wx.MessageDialog(None, u"请按复位键(按住不超过2S,否则板子复位)", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
                dlg.ShowModal()
                dlg.Destroy()
                
            if data[0] == devReply[0] and data[1]==devReply[1] :
                wx.CallAfter(self.window.setItemsText, testItemsEnum['reset'], data[2])
                g_contents.AppendText('test hdmi\n')
                self.cltTestRequest(testItemsEnum['hdmi'])
                self.status = testItemsEnum['hdmi']
        #5. hdmi
        elif testItemsEnum['hdmi'] == self.status:
            if data[0]==devRequst[0] and data[1]==devRequst[1]:
                dlg = wx.MessageDialog(None, u"HDMI是否显示红色", "MessageDialog", wx.YES_NO | wx.ICON_QUESTION)
                if dlg.ShowModal() == wx.ID_YES:
                    wx.CallAfter(self.window.setItemsText, testItemsEnum['hdmi'], 0)
                else:
                     wx.CallAfter(self.window.setItemsText, testItemsEnum['hdmi'], 1)
                dlg.Destroy()
            g_contents.AppendText('test audio\n')
            self.cltTestRequest(testItemsEnum['audio'])
            self.status = testItemsEnum['audio']
        #6. audio
        elif testItemsEnum['audio'] == self.status:
            if data[0]==devRequst[0] and data[1]==devRequst[1]:
                dlg = wx.MessageDialog(None, u"音频口是否有环通输出", "MessageDialog", wx.YES_NO | wx.ICON_QUESTION)
                if dlg.ShowModal() == wx.ID_YES:
                    wx.CallAfter(self.window.setItemsText, testItemsEnum['audio'], 0)
                else:
                     wx.CallAfter(self.window.setItemsText, testItemsEnum['audio'], 1)
                dlg.Destroy()
            g_contents.AppendText('test sata\n')
            self.cltTestRequest(testItemsEnum['sata'])
            self.status = testItemsEnum['sata']
        #7. sata, not support
        elif testItemsEnum['sata'] == self.status:
            if data[0] == devInvalidCmd[0] and data[1]==devInvalidCmd[1] :
                wx.CallAfter(self.window.setItemsText, testItemsEnum['sata'], 1)
                g_contents.AppendText('test usb\n')
                self.cltTestRequest(testItemsEnum['usb'])
                self.status = testItemsEnum['usb']
        #8. usb, not support
        elif testItemsEnum['usb'] == self.status: 
            if data[0] == devInvalidCmd[0] and data[1]==devInvalidCmd[1] :
                wx.CallAfter(self.window.setItemsText, testItemsEnum['usb'], 1)
                g_contents.AppendText('test SD\n')
                self.cltTestRequest(testItemsEnum['sd'])
                self.status = testItemsEnum['sd']
        #9. sd card, not support
        elif testItemsEnum['sd'] == self.status:
            if data[0] == devInvalidCmd[0] and data[1]==devInvalidCmd[1] :
                wx.CallAfter(self.window.setItemsText, testItemsEnum['sd'], 1)
                g_contents.AppendText('test watchdog\n')
                self.cltTestRequest(testItemsEnum['wdg'])
                self.status = testItemsEnum['wdg']
                
        #32. watch dog
        elif testItemsEnum['wdg'] == self.status:
            if data[0]==devRequst[0] and data[1]==devRequst[1]:
                dlg = wx.MessageDialog(None, u"设备是否重启", "MessageDialog", wx.YES_NO | wx.ICON_QUESTION)
                if dlg.ShowModal() == wx.ID_YES:
                    #注意: 这里的枚举值是前一项+1, wdg的枚举值32, 不是顺序导致对话框显示不出信息
                    wx.CallAfter(self.window.setItemsText, testItemsEnum['sd']+1, 0)
                else:
                     wx.CallAfter(self.window.setItemsText, testItemsEnum['sd']+1, 1)
                dlg.Destroy()
            
            g_contents.AppendText('test complete\n')
            self.status = testItemsEnum['none']
            wx.CallAfter(self.window.setItemsText, self.status, 0xaa)
        else:
            pass
        
#建立界面框架
class myFrame(wx.Frame):
    def __init__ (self, parent, id, title):
        dpos = wx.DisplaySize()
        wx.Frame.__init__(self, parent, id, title, pos=(dpos[0]/5, dpos[1]/10), size=(800, 900), style=wx.DEFAULT_FRAME_STYLE )
        
        #def the global variance
        global g_contents
        
        self.itemsText = []
        self.itemsReasonText = []
        self.threads = []
        self.threadId = 0
        self.Bind(wx.EVT_CLOSE, self.closeWin)
        
        #创建垂直sizer
        mainSizer = wx.BoxSizer(wx.VERTICAL)
        mainSizer.Add((-1, 10))
        
        panel=wx.Panel(self)
        panel.SetBackgroundColour('White')
        
        ####### 创建主栏 #############
        devStText = wx.StaticText(panel, -1, u"设备型号:", wx.DefaultPosition, wx.DefaultSize)
        devStText.SetFont(wx.Font(13, wx.DEFAULT, wx.NORMAL, wx.BOLD))
        self.cmbDevType = wx.ComboBox( panel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, devItems, wx.CB_READONLY )
        self.cmbDevType.SetSelection( 0 )
        self.cmbDevType.SetMinSize( wx.Size( 100,-1 ) )
        
        ipStText = wx.StaticText(panel, -1, u"设备IP:", wx.DefaultPosition, wx.DefaultSize)
        ipStText.SetFont(wx.Font(13, wx.DEFAULT, wx.NORMAL, wx.BOLD))
        self.ipText = wx.TextCtrl(panel, -1, "192.168.1.123")
        
        btTst = wx.Button(panel, -1, u"开始测试")   #button1
        btTst.SetFont(wx.Font(11, wx.DEFAULT, wx.NORMAL, wx.BOLD))
        btTst.SetForegroundColour('Blue')
        btTst.Bind(wx.EVT_BUTTON, self.btEvtTst)
        
        btCancel = wx.Button(panel, -1, u"取消")   #button2
        btCancel.SetFont(wx.Font(11, wx.DEFAULT, wx.NORMAL, wx.BOLD))
        btCancel.SetForegroundColour('Red')
        btCancel.Bind(wx.EVT_BUTTON, self.btEvtCancel)
        
        #HORIZONTAL sizer
        mainItemSizer = wx.BoxSizer(wx.HORIZONTAL) #主栏
        mainItemSizer.AddSpacer(sizerspacer, 0, wx.EXPAND, 5)
        mainItemSizer.Add(devStText, 0, wx.ALL, 5)
        mainItemSizer.Add(self.cmbDevType, 0, wx.ALL, 5)
        mainItemSizer.Add(ipStText, 0, wx.ALL, 5)
        mainItemSizer.Add(self.ipText, 0, wx.ALL, 5)
        mainItemSizer.Add((dpos[0]/20, -1))
        mainItemSizer.Add(btTst, 0, wx.ALL, 5)
        mainItemSizer.Add(btCancel, 0, wx.ALL, 5)
        #add to VERTICAL sizer
        mainSizer.Add(mainItemSizer, 0, wx.EXPAND, 5)
        mainSizer.Add(wx.StaticLine(panel), 0, wx.EXPAND, 5)
        mainSizer.Add((-1, 10))
        
        ########## 创建测试项 ###############
        tstItemStText = wx.StaticText(panel, -1, u"测试项", wx.DefaultPosition, wx.DefaultSize)
        tstItemStText.SetFont(wx.Font(12, wx.DEFAULT, wx.NORMAL, wx.NORMAL))
        resultStText = wx.StaticText(panel, -1, u"结果")
        resultStText.SetFont(wx.Font(12, wx.DEFAULT, wx.NORMAL, wx.NORMAL))
        reasonStText = wx.StaticText(panel, -1, u"原因")
        reasonStText.SetFont(wx.Font(12, wx.DEFAULT, wx.NORMAL, wx.NORMAL))
        
        #HORIZONTAL sizer
        tstItemSizer = wx.BoxSizer(wx.HORIZONTAL)
        tstItemSizer.AddSpacer(ststsizerspacer, 0, wx.EXPAND, 5)
        tstItemSizer.Add(tstItemStText, 0, wx.ALL, 5)
        tstItemSizer.Add((200, -1))
        tstItemSizer.Add(resultStText, 0, wx.ALL, 5)
        tstItemSizer.Add((175, -1))
        tstItemSizer.Add(reasonStText, 0, wx.ALL, 5)
        #add to VERTICAL sizer
        mainSizer.Add(tstItemSizer, 0, wx.EXPAND, 5)
        mainSizer.Add((-1, 10))
        
        #创建测试子项
        self.createTestItems(mainSizer, panel);
        mainSizer.Add((-1, 30))
        
        #保存或清除日志
        btSaveLog = wx.Button(panel, -1, u"保存日志")
        btSaveLog.Bind(wx.EVT_BUTTON, self.btEvtSaveLog)
        btClearLog = wx.Button(panel, -1, u"清除日志")
        btClearLog.Bind(wx.EVT_BUTTON, self.btEvtClearLog)
        #HORIZONTAL sizer
        logSizer = wx.BoxSizer(wx.HORIZONTAL)
        logSizer.AddSpacer(ststsizerspacer, 0, wx.EXPAND, 5)
        logSizer.Add(btSaveLog, 0, wx.ALL, 5)
        logSizer.Add((30, -1))
        logSizer.Add(btClearLog, 0, wx.ALL, 5)
        #add to VERTICAL sizer
        mainSizer.Add(logSizer, 0, wx.EXPAND, 5)
        
        #收发日志
        g_contents = wx.TextCtrl(panel, style=wx.TE_MULTILINE|wx.HSCROLL|wx.TE_READONLY)
        mainSizer.Add(g_contents, proportion=1, flag=wx.EXPAND|wx.LEFT|wx.BOTTOM|wx.RIGHT, border=5)
        
        
        #设置面板panel为VERTICAL sizer
        panel.SetSizer(mainSizer)
    
    #创建测试项
    def createTestItems(self, mainSizer, panel):
        for eTestItems, pos in testItems:
            eStText = wx.StaticText(panel, -1, eTestItems, wx.DefaultPosition, wx.DefaultSize)
            eText = wx.TextCtrl(panel, -1, "")
            eText.SetFont(wx.Font(11, wx.DEFAULT, wx.NORMAL, wx.BOLD))
            self.itemsText.append(eText)
            rText = wx.TextCtrl(panel, -1, "", size=(200,-1))
            self.itemsReasonText.append(rText)
            sizer = wx.BoxSizer(wx.HORIZONTAL)
            sizer.AddSpacer(ststsizerspacer, 0, wx.EXPAND, 5)
            sizer.Add(eStText, 0, wx.ALL, 5)
            sizer.Add((pos, -1))
            sizer.Add(eText, 0, wx.ALL, 5)
            sizer.Add((pos/2, -1))
            sizer.Add(rText, 0, wx.ALL, 5)            
            mainSizer.Add(sizer, 0, wx.EXPAND, 5)

    #开始测试按钮事件
    def btEvtTst(self, event):
        self.clearItemsText()
        if not self.threadId:
            thread = socketThread(self, self.ipText.GetValue())
            if thread.socketIsOk():
                self.threads.append(thread)
                thread.start()
                print 'thread: ',self.threads
                g_contents.AppendText('\nstart thread\n')
                self.threadId = 1
            else:
                self.threadId = 0
                dlg = wx.MessageDialog(None, u"连接设备超时,请确认IP是否正确, 或者网线是否OK", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
                dlg.ShowModal()
                dlg.Destroy()
                g_contents.AppendText('\nlink failed\n')
        else:
            dlg = wx.MessageDialog(None, u"已开启测试，请先取消", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
            dlg.ShowModal()
            dlg.Destroy()
    
    #取消按钮测试事件
    def btEvtCancel(self, event):
        self.stopAllThreads()
        self.clearItemsText()
    
    #保存日志
    def btEvtSaveLog(self, event):
        dlg = wx.FileDialog(self, 
            message="Choose a file",
            defaultFile="log.txt",
            wildcard=savewildcard,
            style=wx.SAVE
            )
        if dlg.ShowModal() == wx.ID_OK:
            tmp = ""
            paths = dlg.GetPaths()
            for path in paths:
                tmp = tmp+path
            file=open(tmp,'w')
            file.write(g_contents.GetValue())
            file.close()
        dlg.Destroy()

    #清除日志
    def btEvtClearLog(self, event):
        g_contents.Clear();
    
    #停止线程
    def stopAllThreads(self):
        while self.threads:
            thread = self.threads[0]
            thread.stop()
            self.threads.remove(thread)
            g_contents.AppendText('stop thread\n')
        self.threadId = 0;
        
    #展示测试结果
    def setItemsText(self, item, msg):
        if item == testItemsEnum['none']:
            if 0xaa == msg:
                self.stopAllThreads()
                '''dlg = wx.MessageDialog(None, u"测试完成", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
                dlg.ShowModal()
                dlg.Destroy()'''
        else:
            if msg:
                self.itemsText[item - 1].SetValue('FAIL')
                self.itemsText[item - 1].SetForegroundColour('Red')
                self.itemsReasonText[item-1].SetValue(reasonEnum[item-1])
            else:
                self.itemsText[item - 1].SetValue('SUCCESS')
                self.itemsText[item - 1].SetForegroundColour('Green')
                self.itemsReasonText[item-1].SetValue('none')
            
    #清除测试结果
    def clearItemsText(self):
        for items in self.itemsText:
            items.SetValue('')
        for items in self.itemsReasonText:
            items.SetValue('')
        
    def closeWin(self, event):
        self.stopAllThreads();
        self.Destroy() 
    
#启动应用程序
class myApp(wx.App):
    def OnInit(self):
        self.frame = myFrame(None, -1, title=u"高创单板测试工具")
        self.frame.Show()
        self.SetTopWindow(self.frame)
        return True

########################## Run the program ############################
def main():
    app = myApp()
    app.MainLoop()
    
if __name__ == '__main__':
        main()

