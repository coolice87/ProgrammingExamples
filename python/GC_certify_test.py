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
import time

sizerspacer=(40, -1)
ststsizerspacer=(sizerspacer[0]*2, -1)
HOST = '192.168.1.123'
PORT = 16384

#测试内容
#测试产品型号
devItems = [ u"IVS-FD0X0X" ]
#后面数字为水平便宜,为了对齐
testItems = ((u"报警输入:",175), 
             (u"报警输出:",175), 
             (u"RS485snd:",175),
             (u"RS485rcv:",175),) 
        
testItemsEnum = {'none':0, 'alarmin':1, 'alarmout':2, 'rs485send':3, 'rs485recv':4}

#客户端请求前缀
cltRequest = (0x7D, 0x7B)
#设备端回应前缀
devReply = (0x7D, 0x7D)

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
        
#建立界面框架
class myFrame(wx.Frame):
    def __init__ (self, parent, id, title):
        dpos = wx.DisplaySize()
        wx.Frame.__init__(self, parent, id, title, pos=(dpos[0]/5, dpos[1]/10), size=(700, 700), style=wx.DEFAULT_FRAME_STYLE )
        
        #def the global variance
        global g_contents
        
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
        
        #HORIZONTAL sizer
        mainItemSizer = wx.BoxSizer(wx.HORIZONTAL) #主栏
        mainItemSizer.AddSpacer(sizerspacer, 0, wx.EXPAND, 5)
        mainItemSizer.Add(devStText, 0, wx.ALL, 5)
        mainItemSizer.Add(self.cmbDevType, 0, wx.ALL, 5)
        mainItemSizer.Add(ipStText, 0, wx.ALL, 5)
        mainItemSizer.Add(self.ipText, 0, wx.ALL, 5)
        mainItemSizer.Add((dpos[0]/20, -1))
        #add to VERTICAL sizer
        mainSizer.Add(mainItemSizer, 0, wx.EXPAND, 5)
        mainSizer.Add(wx.StaticLine(panel), 0, wx.EXPAND, 5)
        mainSizer.Add((-1, 10))
        
        #alarm_in HORIZONTAL sizer
        StText = wx.StaticText(panel, -1, u"报警输入:", wx.DefaultPosition, wx.DefaultSize)
        StText.SetFont(wx.Font(11, wx.DEFAULT, wx.NORMAL, wx.BOLD))
        self.alarminText = wx.TextCtrl(panel, -1, "")
        button = wx.Button(panel, -1, u"测试")
        button.Bind(wx.EVT_BUTTON, self.btEvtAlarmin)
        hsizer = wx.BoxSizer(wx.HORIZONTAL)
        hsizer.AddSpacer((40,-1), 0, wx.EXPAND, 5)
        hsizer.Add(StText, 0, wx.ALL, 5)
        hsizer.Add((80, -1))
        hsizer.Add(self.alarminText, 0, wx.ALL, 5)   
        hsizer.Add((80, -1))
        hsizer.Add(button, 0, wx.ALL, 5)  
        mainSizer.Add(hsizer, 0, wx.EXPAND, 5)
        
        #alarm_out HORIZONTAL sizer
        StText = wx.StaticText(panel, -1, u"报警输出:", wx.DefaultPosition, wx.DefaultSize)
        StText.SetFont(wx.Font(11, wx.DEFAULT, wx.NORMAL, wx.BOLD))
        self.alarmoutText = wx.TextCtrl(panel, -1, "0x3")
        button = wx.Button(panel, -1, u"测试")
        button.Bind(wx.EVT_BUTTON, self.btEvtAlarmout)
        hsizer = wx.BoxSizer(wx.HORIZONTAL)
        hsizer.AddSpacer((40,-1), 0, wx.EXPAND, 5)
        hsizer.Add(StText, 0, wx.ALL, 5)
        hsizer.Add((80, -1))
        hsizer.Add(self.alarmoutText, 0, wx.ALL, 5)   
        hsizer.Add((80, -1))
        hsizer.Add(button, 0, wx.ALL, 5)  
        mainSizer.Add(hsizer, 0, wx.EXPAND, 5)

        '''
        #rs485 send HORIZONTAL sizer
        StText = wx.StaticText(panel, -1, u"RS485send:", wx.DefaultPosition, wx.DefaultSize)
        StText.SetFont(wx.Font(11, wx.DEFAULT, wx.NORMAL, wx.BOLD))
        self.rs485sndText = wx.TextCtrl(panel, -1, "1 2 3 4 5 6 7 8")
        button = wx.Button(panel, -1, u"测试")
        button.Bind(wx.EVT_BUTTON, self.btEvtRS485snd)
        hsizer = wx.BoxSizer(wx.HORIZONTAL)
        hsizer.AddSpacer((40,-1), 0, wx.EXPAND, 5)
        hsizer.Add(StText, 0, wx.ALL, 5)
        hsizer.Add((65, -1))
        hsizer.Add(self.rs485sndText, 0, wx.ALL, 5)   
        hsizer.Add((80, -1))
        hsizer.Add(button, 0, wx.ALL, 5)  
        mainSizer.Add(hsizer, 0, wx.EXPAND, 5)
        
        #rs485 recv HORIZONTAL sizer
        StText = wx.StaticText(panel, -1, u"RS485recv:", wx.DefaultPosition, wx.DefaultSize)
        StText.SetFont(wx.Font(11, wx.DEFAULT, wx.NORMAL, wx.BOLD))
        self.rs485rcvText = wx.TextCtrl(panel, -1, '')
        button = wx.Button(panel, -1, u"测试")
        button.Bind(wx.EVT_BUTTON, self.btEvtRS485rcv)
        hsizer = wx.BoxSizer(wx.HORIZONTAL)
        hsizer.AddSpacer((40,-1), 0, wx.EXPAND, 5)
        hsizer.Add(StText, 0, wx.ALL, 5)
        hsizer.Add((65, -1))
        hsizer.Add(self.rs485rcvText, 0, wx.ALL, 5)   
        hsizer.Add((80, -1))
        hsizer.Add(button, 0, wx.ALL, 5)  
        mainSizer.Add(hsizer, 0, wx.EXPAND, 5)
        '''
        
        #添加空行
        mainSizer.Add((-1, 50))
        #收发日志
        g_contents = wx.TextCtrl(panel, style=wx.TE_MULTILINE|wx.HSCROLL|wx.TE_READONLY)
        mainSizer.Add(g_contents, proportion=1, flag=wx.EXPAND|wx.LEFT|wx.BOTTOM|wx.RIGHT, border=5)

        #设置面板panel为VERTICAL sizer
        panel.SetSizer(mainSizer)
    
    def cltTestRequest(self, sk, testItem, value):
        senddata = []
        senddata.append(cltRequest[0])
        senddata.append(cltRequest[1])
        senddata.append(testItem)
        senddata.append(value)
        sk.sendall(dataPack(senddata))
    
    #alarm in button event
    def btEvtAlarmin(self, event):
        if self.ipText.GetValue():
            HOST = self.ipText.GetValue()
        else:
            HOST = '192.168.1.123'
        g_contents.AppendText(u'报警输入:\n')
        
        sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        _running = False
        try:
            sk.settimeout(2)
            sk.connect((HOST, PORT))
            _running = True
            self.cltTestRequest(sk, testItemsEnum['alarmin'], 0)
            '''
            while _running:
                try:
                    buf = sk.recv(1024)
                    data = dataUnpack(buf)
                    if len(data):
                        self.alarminText.SetValue(hex(data[2]))
                except socket.timeout:
                    print 'timeout'
                    break
            '''
            buf = sk.recv(1024)
            data = dataUnpack(buf)
            if len(data):
                self.alarminText.SetValue(hex(data[2]))
            sk.close()
        except Exception, e:
            print 'error', e
            sk.close()
            if False == _running:   
                dlg = wx.MessageDialog(None, u"连接设备超时,请确认IP是否正确, 或者网线是否OK", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
                dlg.ShowModal()
                dlg.Destroy()
            
    #alarm out button event
    def btEvtAlarmout(self, event):
        if self.ipText.GetValue():
            HOST = self.ipText.GetValue()
        else:
            HOST = '192.168.1.123'
        g_contents.AppendText(u'报警输出:\n')
        
        sk = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        _running = False
        try:
            sk.settimeout(2)
            sk.connect((HOST, PORT))
            _running = True
            str = self.alarmoutText.GetValue()
            data = int(str, 16)
            self.cltTestRequest(sk, testItemsEnum['alarmout'], data)
            time.sleep(1)
            sk.close()
        except Exception, e:
            print 'error', e
            sk.close()
            if False == _running:
                dlg = wx.MessageDialog(None, u"连接设备超时,请确认IP是否正确, 或者网线是否OK", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
                dlg.ShowModal()
                dlg.Destroy()

    '''
    #RS485 send button event
    def btEvtRS485snd(self, event):
        pass
    
    #RS485 send button event
    def btEvtRS485rcv(self, event):
        pass
    '''
    def closeWin(self, event):
        self.Destroy() 
    
#启动应用程序
class myApp(wx.App):
    def OnInit(self):
        self.frame = myFrame(None, -1, title=u"高创测试工具")
        self.frame.Show()
        self.SetTopWindow(self.frame)
        return True

########################## Run the program ############################
def main():
    app = myApp()
    app.MainLoop()
    
if __name__ == '__main__':
        main()

