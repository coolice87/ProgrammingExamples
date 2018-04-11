# -*- coding: utf-8 -*- 

###########################################################################
## Python code generated with wxFormBuilder (version Oct  8 2012)
## http://www.wxformbuilder.org/
##
## PLEASE DO "NOT" EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc

###########################################################################
## Class SerialFrameUI
###########################################################################

class SerialFrameUI ( wx.Frame ):
	
	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = wx.EmptyString, pos = wx.DefaultPosition, size = wx.Size( 574,456 ), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL )
		
		self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		self.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INFOBK ) )
		self.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOWFRAME ) )
		
		bSizer1 = wx.BoxSizer( wx.VERTICAL )
		
		bSizer2 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_txtMain = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, wx.TE_MULTILINE|wx.TE_READONLY )
		bSizer2.Add( self.m_txtMain, 1, wx.ALL|wx.EXPAND, 5 )
		
		
		bSizer1.Add( bSizer2, 1, wx.EXPAND, 5 )
		
		bSizer3 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_lblInput = wx.StaticText( self, wx.ID_ANY, u"输入框：", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_lblInput.Wrap( -1 )
		bSizer3.Add( self.m_lblInput, 0, wx.ALL, 5 )
		
		self.m_txtInput = wx.TextCtrl( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer3.Add( self.m_txtInput, 1, wx.ALL, 5 )
		
		self.m_btnSend = wx.Button( self, wx.ID_ANY, u"发送", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer3.Add( self.m_btnSend, 0, wx.ALL, 5 )
		
		self.m_btnClear = wx.Button( self, wx.ID_ANY, u"清除", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer3.Add( self.m_btnClear, 0, wx.ALL, 5 )
		
		self.m_chkHEXShow = wx.CheckBox( self, wx.ID_ANY, u"HEX显示", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer3.Add( self.m_chkHEXShow, 0, wx.ALL, 5 )
		
		
		bSizer1.Add( bSizer3, 0, wx.EXPAND, 5 )
		
		bSizer4 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_lblCOMX = wx.StaticText( self, wx.ID_ANY, u"串口号：", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_lblCOMX.Wrap( -1 )
		bSizer4.Add( self.m_lblCOMX, 0, wx.ALL, 5 )
		
		m_cmbCOMXChoices = [ u"COM1", u"COM2", u"COM3", u"COM4", u"COM5", u"COM6", u"COM7", u"COM8", u"COM9" ]
		self.m_cmbCOMX = wx.ComboBox( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbCOMXChoices, wx.CB_READONLY )
		self.m_cmbCOMX.SetSelection( 0 )
		self.m_cmbCOMX.SetMinSize( wx.Size( 100,-1 ) )
		
		bSizer4.Add( self.m_cmbCOMX, 0, wx.ALL, 5 )
		
		self.m_lblBaud = wx.StaticText( self, wx.ID_ANY, u"波特率：", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_lblBaud.Wrap( -1 )
		bSizer4.Add( self.m_lblBaud, 0, wx.ALL, 5 )
		
		m_cmbBaudChoices = [ u"2400", u"4800", u"9600", u"14400", u"19200", u"28800", u"57600" ]
		self.m_cmbBaud = wx.ComboBox( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbBaudChoices, wx.CB_READONLY )
		self.m_cmbBaud.SetSelection( 6 )
		self.m_cmbBaud.SetMinSize( wx.Size( 100,-1 ) )
		
		bSizer4.Add( self.m_cmbBaud, 0, wx.ALL, 5 )
		
		self.m_btnOpen = wx.Button( self, wx.ID_ANY, u"打开串口", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer4.Add( self.m_btnOpen, 8, wx.ALL, 5 )
		
		
		bSizer4.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_imgStat = wx.StaticBitmap( self, wx.ID_ANY, wx.ArtProvider.GetBitmap( wx.ART_HELP, wx.ART_BUTTON ), wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_imgStat.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOWFRAME ) )
		
		bSizer4.Add( self.m_imgStat, 0, wx.ALL, 5 )
		
		
		bSizer4.AddSpacer( ( 0, 0), 1, wx.EXPAND, 5 )
		
		self.m_chkHEXSend = wx.CheckBox( self, wx.ID_ANY, u"HEX发送", wx.DefaultPosition, wx.DefaultSize, 0 )
		bSizer4.Add( self.m_chkHEXSend, 0, wx.ALL, 5 )
		
		
		bSizer1.Add( bSizer4, 0, wx.EXPAND, 5 )
		
		bSizer5 = wx.BoxSizer( wx.HORIZONTAL )
		
		self.m_lblData = wx.StaticText( self, wx.ID_ANY, u"数据位：", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_lblData.Wrap( -1 )
		bSizer5.Add( self.m_lblData, 0, wx.ALL, 5 )
		
		m_cmbDataChoices = [ u"5", u"6", u"7", u"8" ]
		self.m_cmbData = wx.ComboBox( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbDataChoices, wx.CB_READONLY )
		self.m_cmbData.SetSelection( 3 )
		self.m_cmbData.SetMinSize( wx.Size( 100,-1 ) )
		
		bSizer5.Add( self.m_cmbData, 0, wx.ALL, 5 )
		
		self.m_lblChek = wx.StaticText( self, wx.ID_ANY, u"校验位：", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_lblChek.Wrap( -1 )
		bSizer5.Add( self.m_lblChek, 0, wx.ALL, 5 )
		
		m_cmbChekChoices = [ u"None", u"Odd", u"Even", u"One", u"Zero" ]
		self.m_cmbChek = wx.ComboBox( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbChekChoices, wx.CB_READONLY )
		self.m_cmbChek.SetSelection( 0 )
		self.m_cmbChek.SetMinSize( wx.Size( 100,-1 ) )
		
		bSizer5.Add( self.m_cmbChek, 0, wx.ALL, 5 )
		
		self.m_lblStop = wx.StaticText( self, wx.ID_ANY, u"停止位：", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_lblStop.Wrap( -1 )
		bSizer5.Add( self.m_lblStop, 0, wx.ALL, 5 )
		
		m_cmbStopChoices = [ u"1", u"2" ]
		self.m_cmbStop = wx.ComboBox( self, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbStopChoices, wx.CB_READONLY )
		self.m_cmbStop.SetSelection( 0 )
		self.m_cmbStop.SetMinSize( wx.Size( 100,-1 ) )
		
		bSizer5.Add( self.m_cmbStop, 0, wx.ALL, 5 )
		
		self.m_btnExtn = wx.Button( self, wx.ID_ANY, u"扩展", wx.DefaultPosition, wx.Size( 50,-1 ), 0 )
		bSizer5.Add( self.m_btnExtn, 0, wx.ALL, 5 )
		
		
		bSizer5.AddSpacer( ( 10, 0), 1, wx.EXPAND, 5 )
		
		
		bSizer1.Add( bSizer5, 0, wx.EXPAND, 5 )
		
		
		self.SetSizer( bSizer1 )
		self.Layout()
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.m_btnSend.Bind( wx.EVT_BUTTON, self.on_btnSend_clicked )
		self.m_btnClear.Bind( wx.EVT_BUTTON, self.on_btnClear_clicked )
		self.m_chkHEXShow.Bind( wx.EVT_CHECKBOX, self.on_chkHEXShow_changed )
		self.m_cmbBaud.Bind( wx.EVT_COMBOBOX, self.on_cmbBaud_changled )
		self.m_btnOpen.Bind( wx.EVT_BUTTON, self.on_btnOpen_clicked )
		self.m_btnExtn.Bind( wx.EVT_BUTTON, self.on_btnExtn_clicked )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def on_btnSend_clicked( self, event ):
		event.Skip()
	
	def on_btnClear_clicked( self, event ):
		event.Skip()
	
	def on_chkHEXShow_changed( self, event ):
		event.Skip()
	
	def on_cmbBaud_changled( self, event ):
		event.Skip()
	
	def on_btnOpen_clicked( self, event ):
		event.Skip()
	
	def on_btnExtn_clicked( self, event ):
		event.Skip()
	


from serial import Serial
#from wx.lib.pubsub import Publisher


class SerialFrame(SerialFrameUI):
    def __init__(self,parent=None):
        super(SerialFrame,self).__init__(parent)
        
        self.m_imgStat.SetBitmap(Img_inclosing.getBitmap())
        
        self.Ser = Serial()
        self.serialThread = SerialThread(self.Ser)
        
        #create a pubsub receiver
        #Publisher().subscribe(self.on_txtMain_update,'update')    
        
    def on_txtMain_update(self, msg):
        self.m_txtMain.AppendText(msg.data)
    
    def on_btnSend_clicked( self, event ):
        self.Ser.write(self.m_txtInput.GetValue())
        
    def on_btnClear_clicked( self, event ):
        self.m_txtMain.Clear()
    
    def on_chkHEXShow_changed( self, event ):
        s = self.m_txtMain.GetValue()
        if self.m_chkHEXShow.IsChecked():
            s = ''.join('%02X' %i for i in [ord(c) for c in s])
        else:
            s = ''.join([chr(int(i,16)) for i in [s[i*2:i*2+2] for i in range(0,len(s)/2)]])
        self.m_txtMain.Clear()
        self.m_txtMain.SetValue(s)
        
    def on_cmbBaud_changled( self, event ):
        self.Ser.setBaudrate(int(self.m_cmbBaud.GetValue()))
        
    def on_btnOpen_clicked( self, event ):
        if not self.Ser.isOpen():
            try:
                self.Ser.timeout = 1
                self.Ser.xonxoff = 0
                self.Ser.port = self.m_cmbCOMX.GetValue()
                self.Ser.parity = self.m_cmbChek.GetValue()[0]
                self.Ser.baudrate = int(self.m_cmbBaud.GetValue())
                self.Ser.bytesize = int(self.m_cmbData.GetValue())
                self.Ser.stopbits = int(self.m_cmbStop.GetValue())
                self.Ser.open()
            except Exception,e:
                print 'COMM Open Fail!!',e
            else:
                self.m_btnOpen.SetLabel(u'关闭串口')
                self.m_imgStat.SetBitmap(Img_inopening.getBitmap())
        else:
            self.Ser.close()
            while self.Ser.isOpen(): pass

            self.m_btnOpen.SetLabel(u'打开串口')
            self.m_imgStat.SetBitmap(Img_inclosing.getBitmap())

    
    def on_btnExtn_clicked( self, event ):
        event.Skip()




import time
import threading


class SerialThread(threading.Thread):
    def __init__(self,Ser):
        super(SerialThread,self).__init__()
        
        self.Ser=Ser
        
        self.start()
    
    def run(self):
        while True:            
            if self.Ser.isOpen() and self.Ser.inWaiting():
                text = self.Ser.read(self.Ser.inWaiting())
                wx.CallAfter(Publisher().sendMessage('update',text))
                
            time.sleep(0.01)
                            


from wx.lib import embeddedimage

Img_inclosing = embeddedimage.PyEmbeddedImage(
    "iVBORw0KGgoAAAANSUhEUgAAABQAAAAUCAIAAAAC64paAAAAAXNSR0IArs4c6QAAAARnQU1B"
    "AACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAABiSURBVDhPY/iPDTBgAOzK0EQxtSGL"
    "oCtG5uPXCZFFUQ/nEKMTTT/UJOJ1IusHaSZVJ1z/AGkmz70jXBfZ8QxNq+QFH8hWsm2GaiZD"
    "PyQ7IbIY8Y5HZETq5GeoS/A6AK0kAQCtTO8ROTKfPAAAAABJRU5ErkJggg==")


Img_inopening = embeddedimage.PyEmbeddedImage(
    "iVBORw0KGgoAAAANSUhEUgAAABQAAAAUCAYAAACNiR0NAAAAAXNSR0IArs4c6QAAAARnQU1B"
    "AACxjwv8YQUAAAAJcEhZcwAADsIAAA7CARUoSoAAAACKSURBVDhPY/wPBAw4wDtZVawyQo9v"
    "49LCwIjNQFwGoZuCzWAmdEXEGgbSh00tioGkGAZzCLoeuIHkGIbNULCBlBiGbihGGOKMPiIl"
    "qGogyKeMb2VUcKZDIh2FooyqLgSZPBINxJfRBzxSQI6jTaRQw9swM+AupMRQZL0oXibHUHQ9"
    "GGFIiqHY1AIAg2UtGigTDxsAAAAASUVORK5CYII=")




if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = SerialFrame()
    frame.Show(True)
    app.MainLoop()
