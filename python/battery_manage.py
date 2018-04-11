# -*- coding: utf-8 -*- 

#---------------------------------------------------------------------
#Name:   a simple editor
#Author:    Sharedelin
#Created:   2016/08/04
#Licence:   
#---------------------------------------------------------------------

#import kinds of lib
import time
import serial
import wx
import wx.xrc
import binascii
import struct
import crc16

from wx.lib import embeddedimage
	
print wx.version()

#################### set the file filter ##############################
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

global rcv_wait_timeout, modbus_dev_addr
rcv_wait_timeout = 300
modbus_dev_addr = 0x01
func_code_invalid_mask = 0x80
	
######################### class and function #########################

class crc16:  
	auchCRCHi = [0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  \
				0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  \
				0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,  \
				0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  \
				0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  \
				0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  \
				0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  \
				0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  \
				0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  \
				0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  \
				0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,  \
				0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  \
				0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,0x80, 0x41, 0x00, 0xC1, 0x81, 0x40] 

	auchCRCLo = [0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,  \
				0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,  \
				0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,  \
				0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,  \
				0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,  \
				0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,  \
				0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,  \
				0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,  \
				0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,  \
				0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,  \
				0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,  \
				0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,  \
				0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,0x43, 0x83, 0x41, 0x81, 0x80, 0x40 ]
	
	def __init__(self):  
		pass  
	
	def calcrc(self,array):  
		uchCRCHi = 0xFF
		uchCRCLo = 0xFF  
		for i in range(0,len(array)):
			uIndex = uchCRCLo ^ array[i]
			uchCRCLo = uchCRCHi ^ self.auchCRCHi[uIndex]
			uchCRCHi = self.auchCRCLo[uIndex]
		return (uchCRCHi<<8 | uchCRCLo)  
	
	def createarray(self,array):  
		crcvalue = self.calcrc(array)  
		array.append(crcvalue>>8)  
		array.append(crcvalue&0xff)  
		return array

	def judgecrc(self,array):  
		uchCRCHi = 0xff  
		uchCRCLo = 0xff  
		lenarray = len(array)  
		for i in range(0,lenarray-2):  
			uIndex = uchCRCLo ^ array[i]
			uchCRCLo = uchCRCHi ^ self.auchCRCHi[uIndex]
			uchCRCHi = self.auchCRCLo[uIndex] 
		#print '%x %x'%(uchCRCHi, uchCRCLo)
		if uchCRCHi == array[lenarray-2] and uchCRCLo== array[lenarray-1] :  
			return 1  
		else:  
			return 0		

class serial_fram_ui(wx.Frame):
	#init
	def __init__(self):
		wx.Frame.__init__(self, None, wx.ID_ANY, "batter manage", pos =(-1, 0), size =(1000, 650), style = wx.DEFAULT_FRAME_STYLE|wx.TAB_TRAVERSAL)
		
		#self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		#self.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INFOBK ) )
		#self.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOWFRAME ) )
		#self.SetForegroundColour("Black")
		#self.SetBackgroundColour("White")
		
		panel = wx.Panel(self, wx.ID_ANY)
		
		#vertical boxsizer
		vboxsizer1 = wx.BoxSizer( wx.VERTICAL )
		
		#*********** horizonal 1****************#
		hboxsizer1 = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer1.AddSpacer( ( 20, 0), 0, wx.EXPAND, 5 )
		
		self.m_lblCOMX = wx.StaticText( panel, wx.ID_ANY, "串口号：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_lblCOMX.Wrap( -1 )
		hboxsizer1.Add( self.m_lblCOMX, 0, wx.ALL, 5 )
		
		m_cmbCOMXChoices = [ u"COM1", u"COM2", u"COM3", u"COM4", u"COM5", u"COM6", u"COM7", u"COM8", u"COM9", \
							u"COM10", u"COM11", u"COM12", u"COM13", u"COM14", u"COM15", u"COM16", u"COM17", u"COM18", u"COM19"]
		self.m_cmbCOMX = wx.ComboBox( panel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbCOMXChoices, wx.CB_READONLY )
		self.m_cmbCOMX.SetSelection( 0 )
		self.m_cmbCOMX.SetMinSize( wx.Size( 100,-1 ) )
		hboxsizer1.Add( self.m_cmbCOMX, 0, wx.ALL, 5 )
		
		self.m_lblBaud = wx.StaticText( panel, wx.ID_ANY, "波特率：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_lblBaud.Wrap( -1 )
		hboxsizer1.Add( self.m_lblBaud, 0, wx.ALL, 5 )
		
		m_cmbBaudChoices = [ u"2400", u"4800", u"9600", u"14400", u"19200", u"28800", u"57600", u"115200" ]
		self.m_cmbBaud = wx.ComboBox( panel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbBaudChoices, wx.CB_READONLY )
		self.m_cmbBaud.SetSelection( 2 )
		self.m_cmbBaud.SetMinSize( wx.Size( 100,-1 ) )
		hboxsizer1.Add( self.m_cmbBaud, 0, wx.ALL, 5 )
		
		self.m_lblData = wx.StaticText( panel, wx.ID_ANY, "数据位：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_lblData.Wrap( -1 )
		hboxsizer1.Add( self.m_lblData, 0, wx.ALL, 5 )
		
		m_cmbDataChoices = [ u"5", u"6", u"7", u"8" ]
		self.m_cmbData = wx.ComboBox( panel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbDataChoices, wx.CB_READONLY )
		self.m_cmbData.SetSelection( 3 )
		self.m_cmbData.SetMinSize( wx.Size( 100,-1 ) )
		hboxsizer1.Add( self.m_cmbData, 0, wx.ALL, 5 )
		
		self.m_lblChek = wx.StaticText( panel, wx.ID_ANY, "校验位：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_lblChek.Wrap( -1 )
		hboxsizer1.Add( self.m_lblChek, 0, wx.ALL, 5 )
		
		m_cmbChekChoices = [ u"None", u"Odd", u"Even", u"One", u"Zero" ]
		self.m_cmbChek = wx.ComboBox( panel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbChekChoices, wx.CB_READONLY )
		self.m_cmbChek.SetSelection( 0 )
		self.m_cmbChek.SetMinSize( wx.Size( 100,-1 ) )
		hboxsizer1.Add( self.m_cmbChek, 0, wx.ALL, 5 )
		
		self.m_lblStop = wx.StaticText( panel, wx.ID_ANY, "停止位：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_lblStop.Wrap( -1 )
		hboxsizer1.Add( self.m_lblStop, 0, wx.ALL, 5 )
		
		m_cmbStopChoices = [ u"1", u"2" ]
		self.m_cmbStop = wx.ComboBox( panel, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, m_cmbStopChoices, wx.CB_READONLY )
		self.m_cmbStop.SetSelection( 0 )
		self.m_cmbStop.SetMinSize( wx.Size( 100,-1 ) )
		hboxsizer1.Add( self.m_cmbStop, 0, wx.ALL, 5 )
		
		#add horizonal 1 to vbox
		vboxsizer1.Add( hboxsizer1, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 2****************#
		hboxsizer2 = wx.BoxSizer( wx.HORIZONTAL )
		
		hboxsizer2.AddSpacer( ( 20, 0), 0, wx.EXPAND, 5 )
		
		self.m_imgStat = wx.StaticBitmap( panel, wx.ID_ANY, wx.ArtProvider.GetBitmap( wx.ART_HELP, wx.ART_BUTTON ), wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_imgStat.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOWFRAME ) )
		self.m_imgStat.SetBitmap(Img_inclosing.getBitmap())
		hboxsizer2.Add( self.m_imgStat, 0, wx.ALL, 5 )
		
		self.m_btnOpen = wx.Button( panel, wx.ID_ANY, "打开串口", wx.DefaultPosition, wx.DefaultSize, 0 )
		hboxsizer2.Add( self.m_btnOpen, 0, wx.ALL, 5 )
		
		self.m_btnClear = wx.Button( panel, wx.ID_ANY, "清除串口", wx.DefaultPosition, wx.DefaultSize, 0 )
		hboxsizer2.Add( self.m_btnClear, 0, wx.ALL, 5 )
		
		#add horizonal 2 to vbox
		vboxsizer1.Add( hboxsizer2, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 3-label ****************#
		hboxsizer3_lab = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer3_lab.AddSpacer( ( 0, 0), 0, wx.EXPAND, 5 )
		
		self.m_vol_lab = wx.StaticText( panel, wx.ID_ANY, "电压KB值计算", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_lab.Wrap( -1 )
		hboxsizer3_lab.Add( self.m_vol_lab, 1, wx.ALL, 5 )
		
		#add horizonal 3 to vbox
		vboxsizer1.Add( hboxsizer3_lab, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 3_1****************#
		hboxsizer3_1 = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer3_1.AddSpacer( ( 150, 0), 0, wx.EXPAND, 5 )
		
		self.m_vol_v1 = wx.StaticText( panel, wx.ID_ANY, "电压值1：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_v1.Wrap( -1 )
		hboxsizer3_1.Add( self.m_vol_v1, 0, wx.ALL, 5 )
		
		self.m_vol_m1 = wx.StaticText( panel, wx.ID_ANY, "测量值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_m1.Wrap( -1 )
		hboxsizer3_1.Add( self.m_vol_m1, 0, wx.ALL, 5 )
		self.m_vol_m1_text = wx.TextCtrl(panel)
		self.m_vol_m1_text.WriteText('0')
		hboxsizer3_1.Add(self.m_vol_m1_text, proportion = 0, flag=wx.LEFT, border=5)
		
		self.m_vol_r1 = wx.StaticText( panel, wx.ID_ANY, "实际值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_r1.Wrap( -1 )
		hboxsizer3_1.Add( self.m_vol_r1, 0, wx.ALL, 5 )
		self.m_vol_r1_text = wx.TextCtrl(panel)
		self.m_vol_r1_text.WriteText('0')
		hboxsizer3_1.Add(self.m_vol_r1_text, proportion = 0, flag=wx.LEFT, border=5)

		#self.m_volKB_calc = wx.Button( panel, wx.ID_ANY, "计算", wx.DefaultPosition, wx.DefaultSize, 0 )
		#hboxsizer3_1.Add( self.m_volKB_calc, 0, wx.EXPAND, 5 )
		self.m_volKB_calc = wx.Button( panel, wx.ID_ANY, "计算", pos =(580, 120), size =(90, 28), style =0 )
		
		#add horizonal 3 to vbox
		vboxsizer1.Add( hboxsizer3_1, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 3_2****************#
		hboxsizer3_2 = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer3_2.AddSpacer( ( 150, 0), 0, wx.EXPAND, 5 )
		
		self.m_vol_v2 = wx.StaticText( panel, wx.ID_ANY, "电压值2：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_v2.Wrap( -1 )
		hboxsizer3_2.Add( self.m_vol_v2, 0, wx.ALL, 5 )
		
		self.m_vol_m2 = wx.StaticText( panel, wx.ID_ANY, "测量值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_m2.Wrap( -1 )
		hboxsizer3_2.Add( self.m_vol_m2, 0, wx.ALL, 5 )
		self.m_vol_m2_text = wx.TextCtrl(panel)
		self.m_vol_m2_text.WriteText('0')
		hboxsizer3_2.Add(self.m_vol_m2_text, proportion = 0, flag=wx.LEFT, border=5)
		
		self.m_vol_r2 = wx.StaticText( panel, wx.ID_ANY, "实际值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_r2.Wrap( -1 )
		hboxsizer3_2.Add( self.m_vol_r2, 0, wx.ALL, 5 )
		self.m_vol_r2_text = wx.TextCtrl(panel)
		self.m_vol_r2_text.WriteText('0')
		hboxsizer3_2.Add(self.m_vol_r2_text, proportion = 0, flag=wx.LEFT, border=5)
		
		#add horizonal 3 to vbox
		vboxsizer1.Add( hboxsizer3_2, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 3_3****************#
		hboxsizer3_3 = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer3_3.AddSpacer( ( 150, 0), 0, wx.EXPAND, 5 )
		
		self.m_vol_KB = wx.StaticText( panel, wx.ID_ANY, "电压(KB值)：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_KB.Wrap( -1 )
		hboxsizer3_3.Add( self.m_vol_KB, 0, wx.ALL, 5 )
		
		self.m_vol_K = wx.StaticText( panel, wx.ID_ANY, "K值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_K.Wrap( -1 )
		hboxsizer3_3.Add( self.m_vol_K, 0, wx.ALL, 5 )
		self.m_vol_K_text = wx.TextCtrl(panel)
		self.m_vol_K_text.WriteText('1.0')
		hboxsizer3_3.Add(self.m_vol_K_text, proportion = 0, flag=wx.LEFT, border=5)
		
		self.m_vol_B = wx.StaticText( panel, wx.ID_ANY, "B值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_B.Wrap( -1 )
		hboxsizer3_3.Add( self.m_vol_B, 0, wx.ALL, 5 )
		self.m_vol_B_text = wx.TextCtrl(panel)
		self.m_vol_B_text.WriteText('0.0')
		hboxsizer3_3.Add(self.m_vol_B_text, proportion = 0, flag=wx.LEFT, border=5)
		
		#self.m_volKB_read = wx.Button( panel, wx.ID_ANY, "读取", wx.DefaultPosition, wx.DefaultSize, 0 )
		#hboxsizer3_3.Add( self.m_volKB_read, 0, wx.LEFT, 5 )
		self.m_volKB_read = wx.Button( panel, wx.ID_ANY, "读取", pos =(580, 160), size =(90, 28), style =0)
		#self.m_volKB_set = wx.Button( panel, wx.ID_ANY, "设置", wx.DefaultPosition, wx.DefaultSize, 0 )
		#hboxsizer3_3.Add( self.m_volKB_set, 0, wx.LEFT, 5 )
		self.m_volKB_set = wx.Button( panel, wx.ID_ANY, "设置", pos =(680, 160), size =(90, 28), style =0)
		
		#add horizonal 3 to vbox
		vboxsizer1.Add( hboxsizer3_3, 0, wx.EXPAND, 5 )

		#*********** horizonal 4-label ****************#
		hboxsizer4_lab = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer4_lab.AddSpacer( ( 0, 0), 0, wx.EXPAND, 5 )
		
		self.m_cur_lab = wx.StaticText( panel, wx.ID_ANY, "电流KB值计算", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_lab.Wrap( -1 )
		hboxsizer4_lab.Add( self.m_cur_lab, 1, wx.ALL, 5 )
		
		#add horizonal 3 to vbox
		vboxsizer1.Add( hboxsizer4_lab, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 4_1****************#
		hboxsizer4_1 = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer4_1.AddSpacer( ( 150, 0), 0, wx.EXPAND, 5 )
		
		self.m_cur_v1 = wx.StaticText( panel, wx.ID_ANY, "电流值1：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_v1.Wrap( -1 )
		hboxsizer4_1.Add( self.m_cur_v1, 0, wx.ALL, 5 )
		
		self.m_cur_m1 = wx.StaticText( panel, wx.ID_ANY, "测量值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_m1.Wrap( -1 )
		hboxsizer4_1.Add( self.m_cur_m1, 0, wx.ALL, 5 )
		self.m_cur_m1_text = wx.TextCtrl(panel)
		self.m_cur_m1_text.WriteText('0')
		hboxsizer4_1.Add(self.m_cur_m1_text, proportion = 0, flag=wx.LEFT, border=5)
		
		self.m_cur_r1 = wx.StaticText( panel, wx.ID_ANY, "实际值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_r1.Wrap( -1 )
		hboxsizer4_1.Add( self.m_cur_r1, 0, wx.ALL, 5 )
		self.m_cur_r1_text = wx.TextCtrl(panel)
		self.m_cur_r1_text.WriteText('0')
		hboxsizer4_1.Add(self.m_cur_r1_text, proportion = 0, flag=wx.LEFT, border=5)
		
		#self.m_curKB_calc = wx.Button( panel, wx.ID_ANY, "计算", wx.DefaultPosition, wx.DefaultSize, 0 )
		#hboxsizer4_1.Add( self.m_curKB_calc, 0, wx.ALL, 5 )
		self.m_curKB_calc = wx.Button( panel, wx.ID_ANY, "计算", pos =(580, 230), size =(90, 28), style =0 )
		
		#add horizonal 3 to vbox
		vboxsizer1.Add( hboxsizer4_1, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 4_2****************#
		hboxsizer4_2 = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer4_2.AddSpacer( ( 150, 0), 0, wx.EXPAND, 5 )
		
		self.m_cur_v2 = wx.StaticText( panel, wx.ID_ANY, "电流值2：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_v2.Wrap( -1 )
		hboxsizer4_2.Add( self.m_cur_v2, 0, wx.ALL, 5 )
		
		self.m_cur_m2 = wx.StaticText( panel, wx.ID_ANY, "测量值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_m2.Wrap( -1 )
		hboxsizer4_2.Add( self.m_cur_m2, 0, wx.ALL, 5 )
		self.m_cur_m2_text = wx.TextCtrl(panel)
		self.m_cur_m2_text.WriteText('0')
		hboxsizer4_2.Add(self.m_cur_m2_text, proportion = 0, flag=wx.LEFT, border=5)
		
		self.m_cur_r2 = wx.StaticText( panel, wx.ID_ANY, "实际值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_r2.Wrap( -1 )
		hboxsizer4_2.Add( self.m_cur_r2, 0, wx.ALL, 5 )
		self.m_cur_r2_text = wx.TextCtrl(panel)
		self.m_cur_r2_text.WriteText('0')
		hboxsizer4_2.Add(self.m_cur_r2_text, proportion = 0, flag=wx.LEFT, border=5)
		
		#add horizonal 3 to vbox
		vboxsizer1.Add( hboxsizer4_2, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 4_3****************#
		hboxsizer4_3 = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer4_3.AddSpacer( ( 150, 0), 0, wx.EXPAND, 5 )
		
		self.m_cur_KB = wx.StaticText( panel, wx.ID_ANY, "电流(KB值)：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_KB.Wrap( -1 )
		hboxsizer4_3.Add( self.m_cur_KB, 0, wx.ALL, 5 )
		
		self.m_cur_K = wx.StaticText( panel, wx.ID_ANY, "K值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_K.Wrap( -1 )
		hboxsizer4_3.Add( self.m_cur_K, 0, wx.ALL, 5 )
		self.m_cur_K_text = wx.TextCtrl(panel)
		self.m_cur_K_text.WriteText('1.0')
		hboxsizer4_3.Add(self.m_cur_K_text, proportion = 0, flag=wx.LEFT, border=5)
		
		self.m_cur_B = wx.StaticText( panel, wx.ID_ANY, "B值：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_cur_B.Wrap( -1 )
		hboxsizer4_3.Add( self.m_cur_B, 0, wx.ALL, 5 )
		self.m_cur_B_text = wx.TextCtrl(panel)
		self.m_cur_B_text.WriteText('0.0')
		hboxsizer4_3.Add(self.m_cur_B_text, proportion = 0, flag=wx.LEFT, border=5)
		
		#self.m_curKB_read = wx.Button( panel, wx.ID_ANY, "读取", wx.DefaultPosition, wx.DefaultSize, 0 )
		#hboxsizer4_3.Add( self.m_curKB_read, 0, wx.ALL, 5 )
		self.m_curKB_read = wx.Button( panel, wx.ID_ANY, "读取", pos =(580, 270), size =(90, 28), style =0)
		#self.m_curKB_set = wx.Button( panel, wx.ID_ANY, "设置", wx.DefaultPosition, wx.DefaultSize, 0 )
		#hboxsizer4_3.Add( self.m_curKB_set, 0, wx.ALL, 5 )
		self.m_curKB_set = wx.Button( panel, wx.ID_ANY, "设置", pos =(680, 270), size =(90, 28), style =0)
		
		#add horizonal 4 to vbox
		vboxsizer1.Add( hboxsizer4_3, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 5-label ****************#
		hboxsizer5_lab = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer5_lab.AddSpacer( ( 0, 0), 0, wx.EXPAND, 5 )
		
		self.m_vref_lab = wx.StaticText( panel, wx.ID_ANY, "", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vref_lab.Wrap( -1 )
		hboxsizer5_lab.Add( self.m_vref_lab, 1, wx.ALL, 5 )
		
		#add horizonal 3 to vbox
		vboxsizer1.Add( hboxsizer5_lab, 0, wx.EXPAND, 5 )
		
		#*********** horizonal 5****************#
		hboxsizer5 = wx.BoxSizer( wx.HORIZONTAL )
		hboxsizer5.AddSpacer( ( 150, 0), 0, wx.EXPAND, 5 )
		
		self.m_vol_ref = wx.StaticText( panel, wx.ID_ANY, "AD参考电压(mv)：", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTER )
		self.m_vol_ref.Wrap( -1 )
		hboxsizer5.Add( self.m_vol_ref, 0, wx.ALL, 5 )
		
		self.m_vol_ref_text = wx.TextCtrl(panel)
		self.m_vol_ref_text.WriteText('2500')
		hboxsizer5.Add(self.m_vol_ref_text, proportion = 0, flag=wx.LEFT, border=5)
		
		#self.m_volref_read = wx.Button( panel, wx.ID_ANY, "读取", wx.DefaultPosition, wx.DefaultSize, 0 )
		#hboxsizer5.Add( self.m_volref_read, 0, wx.ALL, 5 )
		self.m_volref_read = wx.Button( panel, wx.ID_ANY, "读取", pos =(400, 325), size =(90, 28), style =0)
		#self.m_volref_set = wx.Button( panel, wx.ID_ANY, "设置", wx.DefaultPosition, wx.DefaultSize, 0 )
		#hboxsizer5.Add( self.m_volref_set, 0, wx.ALL, 5 )
		self.m_volref_set = wx.Button( panel, wx.ID_ANY, "设置", pos =(500, 325), size =(90, 28), style =0)
		
		#add horizonal 5 to vbox
		vboxsizer1.Add( hboxsizer5, 0, wx.EXPAND, 5 )
		
		#*********** com contents ****************#
		self.m_contents = wx.TextCtrl(panel, style=wx.TE_MULTILINE|wx.HSCROLL|wx.TE_READONLY)
		vboxsizer1.Add(self.m_contents, proportion=1, flag=wx.EXPAND|wx.LEFT|wx.BOTTOM|wx.RIGHT, border=5)
		
		#***************************************#
		panel.SetSizer(vboxsizer1)
		
		#bind the button event
		self.m_cmbBaud.Bind( wx.EVT_COMBOBOX, self.on_cmbBaud_changled )
		self.m_btnOpen.Bind(wx.EVT_BUTTON, self.openclose)
		self.m_btnClear.Bind(wx.EVT_BUTTON, self.clearcom)
		self.m_volKB_calc.Bind(wx.EVT_BUTTON, self.vol_kb_calc)
		self.m_volKB_read.Bind(wx.EVT_BUTTON, self.vol_kb_read)
		self.m_volKB_set.Bind(wx.EVT_BUTTON, self.vol_kb_set)
		self.m_curKB_calc.Bind(wx.EVT_BUTTON, self.cur_kb_calc)
		self.m_curKB_read.Bind(wx.EVT_BUTTON, self.cur_kb_read)
		self.m_curKB_set.Bind(wx.EVT_BUTTON, self.cur_kb_set)
		self.m_volref_read.Bind(wx.EVT_BUTTON, self.vol_ref_read)
		self.m_volref_set.Bind(wx.EVT_BUTTON, self.vol_ref_set)
		
		#**************** serial *************#
		self.Ser = serial.Serial()
	
		#clear com data
	def clearcom(self, event):
		self.m_contents.Clear();
	
	#set baud
	def on_cmbBaud_changled(self, event):
		print int(self.m_cmbBaud.GetValue())
		self.Ser.setBaudrate(int(self.m_cmbBaud.GetValue()))
	
	#open and close com
	def openclose(self, event):
		if not self.Ser.isOpen():
			try:
				self.Ser.timeout = 1
				self.Ser.xonxoff = 0
				self.Ser.port = self.m_cmbCOMX.GetSelection()
				self.Ser.parity = self.m_cmbChek.GetValue()[0]
				self.Ser.baudrate = int(self.m_cmbBaud.GetValue())
				self.Ser.bytesize = int(self.m_cmbData.GetValue())
				self.Ser.stopbits = int(self.m_cmbStop.GetValue())
				
				self.Ser.open()

			except Exception,e:
				print 'COMM Open Fail!!',e
				dlg=wx.MessageDialog(self,"串口不存在", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
				dlg.ShowModal()
			else:
				self.m_btnOpen.SetLabel('关闭串口')
				self.m_imgStat.SetBitmap(Img_inopening.getBitmap())
		else:
			self.Ser.close()
			while self.Ser.isOpen(): pass

			self.m_btnOpen.SetLabel('打开串口')
			self.m_imgStat.SetBitmap(Img_inclosing.getBitmap())
	
	#judge uart open
	def serial_is_open(self):
		if not self.Ser.isOpen():
			dlg=wx.MessageDialog(self,"请先打开串口", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
			dlg.ShowModal()
			return 0
		else:
			return 1
	
	#show send or receive data, flag=1:show send, 0: show receive
	def show_snd_rcv_data(self, array, flag):
		if flag: #send data
			self.m_contents.AppendText('send: ')
			for i in range(0, len(array)):
				self.m_contents.AppendText(hex(array[i])+' ')
			self.m_contents.AppendText('\n')
		else: #rcv data
			self.m_contents.AppendText('receive: ')
			for i in range(0, len(array)):
				self.m_contents.AppendText(hex(array[i])+' ')
			self.m_contents.AppendText('\n')
	
	#wait send response
	def set_send_response(self):
		timeout = 0
		rcv_bytes = ''
		while True:
			if self.Ser.isOpen() and self.Ser.inWaiting():
				rcv_bytes = self.Ser.read(64)
				break
			else:
				time.sleep(0.01)
				timeout += 1
			if timeout > rcv_wait_timeout:
				self.m_contents.AppendText('wait receive timeout\n')
				break
		
		#deal with data
		rcv_arr = []
		if len(rcv_bytes):
			for i in range(0, len(rcv_bytes)):
				rcv_arr.append(struct.unpack("B", rcv_bytes[i])[0])
			self.show_snd_rcv_data(rcv_arr, 0)
			#CRC16
			crc_16 = crc16()
			crc_ret = crc_16.judgecrc(rcv_arr)
			if crc_ret:
				self.m_contents.AppendText('set: success\n')
				self.m_contents.AppendText('\n')
				return 1, rcv_arr
			else:
				self.m_contents.AppendText('set: fail\n')
				self.m_contents.AppendText('\n')
				return 0, rcv_arr
		else:
			return 0, rcv_arr
		
	#receive data
	def read_receive_data(self):
		timeout = 0
		rcv_bytes = ''
		while True:
			if self.Ser.isOpen() and self.Ser.inWaiting():
				rcv_bytes = self.Ser.read(64)
				break
			else:
				time.sleep(0.01)
				timeout += 1
			if timeout > rcv_wait_timeout:
				self.m_contents.AppendText('wait receive timeout\n')
				self.m_contents.AppendText('\n')
				break
		
		#deal with data
		rcv_arr = []
		if len(rcv_bytes):
			for i in range(0, len(rcv_bytes)):
				rcv_arr.append(struct.unpack("B", rcv_bytes[i])[0])
			self.show_snd_rcv_data(rcv_arr, 0)
			#CRC16
			crc_16 = crc16()
			crc_ret = crc_16.judgecrc(rcv_arr)
			if crc_ret:
				self.m_contents.AppendText('read: success\n')
				self.m_contents.AppendText('\n')
				return 1, rcv_arr
			else:
				self.m_contents.AppendText('read: fail\n')
				self.m_contents.AppendText('\n')
				return 0, rcv_arr
		else:		
			return 0, rcv_arr
	
	def vol_kb_calc(self, event):
		Vm1 = float(self.m_vol_m1_text.GetValue())
		Vr1 = float(self.m_vol_r1_text.GetValue())
		Vm2 = float(self.m_vol_m2_text.GetValue())
		Vr2 = float(self.m_vol_r2_text.GetValue())
		print Vm1, Vr1, Vm2, Vr2
		
		# Vr = k*Vm + b
		if Vm2 > Vm1 and Vr2 > Vr1 :
			tmp_Vm = Vm2 - Vm1
			tmp_Vr = Vr2 - Vr1
			K = tmp_Vr / tmp_Vm
			B = Vr1 - K *Vm1
			print K, B
			K = float('%.3f'%K)
			B = float('%.3f'%B)
			self.m_vol_K_text.SetValue(str(K))
			self.m_vol_B_text.SetValue(str(B))
		else:
			dlg=wx.MessageDialog(self,"测量数据不对，请检查", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
			dlg.ShowModal()
		
	#read vol kb from hardware
	#response test: 1 4 2 3 e8 3 e7 4E B3
	#response fail: 1 84 1 7 D0 5C 63
	def vol_kb_read(self, event):
		if self.serial_is_open():
			#************ send **************#
			send_arr = []
			#1.dev modbus addr
			send_arr.append(modbus_dev_addr)
			#2.func code
			send_arr.append(0x04)
			#3.register addr
			send_arr.append(0x00)
			send_arr.append(0x02)
			#4. register count
			send_arr.append(0x00)
			send_arr.append(0x02)
			
			#5.CRC16
			crc_16 = crc16()
			crcvalue = crc_16.calcrc(send_arr)
			#print '%x'%crcvalue
			send_arr.append((crcvalue>>8) & 0xff)
			send_arr.append(crcvalue & 0xff)
			
			#change to bytes
			snd_bytes = ''
			for i in range(0, len(send_arr)):
				snd_bytes = snd_bytes + struct.pack("B", send_arr[i])
			self.show_snd_rcv_data(send_arr, 1)
			#send by uart
			self.Ser.flushInput()
			self.Ser.write(snd_bytes)
			
			#************ receive *************#
			ret, rcv_data = self.read_receive_data()
			if ret:
				if rcv_data[1] & func_code_invalid_mask:
					dlg=wx.MessageDialog(self,"地址或数据有误", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
					dlg.ShowModal()
				else:
					value = rcv_data[3] << 8 
					value += rcv_data[4]
					print value
					fval = float(value) / 1000
					self.m_vol_K_text.SetValue(str(fval))
					value = rcv_data[5] << 8 
					value += rcv_data[6]
					if value > 32768:
						value = value - 65536
					print value
					fval = float(value) / 1000
					self.m_vol_B_text.SetValue(str(fval))
					
	#set vol kb to hardware
	#response test: 1 10 0 2 0 2 08 E0
	#response fail: 1 86 2 A1 C3
	def vol_kb_set(self, event):
		if self.serial_is_open():
			#************ send **************#
			send_arr = []
			#1.dev modbus addr
			send_arr.append(modbus_dev_addr)
			#2.func code
			send_arr.append(0x10)
			#3.register addr
			send_arr.append(0x00)
			send_arr.append(0x02)
			#4. register count
			send_arr.append(0x00)
			send_arr.append(0x02)
			#5. register data len
			send_arr.append(0x04)
			
			#6-1.vol K value
			fk = float(self.m_vol_K_text.GetValue()) * 1000
			k = int(fk)
			send_arr.append((k>>8) & 0xff)
			send_arr.append(k & 0xff)
			#6-2.vol B value
			fb = float(self.m_vol_B_text.GetValue()) * 1000
			b = int(fb)
			send_arr.append((b>>8) & 0xff)
			send_arr.append(b & 0xff)
			print k ,b, send_arr
			'''
			if k > 1500 or b > 1000:
				dlg=wx.MessageDialog(self,"k<=1500, b<=1000", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
				dlg.ShowModal()
				return None
			'''
			#7.CRC16
			crc_16 = crc16()
			crcvalue = crc_16.calcrc(send_arr)
			#print '%x'%crcvalue
			send_arr.append((crcvalue>>8) & 0xff)
			send_arr.append(crcvalue & 0xff)
			
			#change to bytes
			bytes = ''
			for i in range(0, len(send_arr)):
				bytes = bytes + struct.pack("B", send_arr[i])
			self.show_snd_rcv_data(send_arr, 1)
			#send by uart
			self.Ser.flushInput()
			self.Ser.write(bytes)
			
			#************ receive response *************#
			ret, rcv_data = self.set_send_response()
			if ret and rcv_data[1] & func_code_invalid_mask:
				dlg=wx.MessageDialog(self,"地址或数据有误", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
				dlg.ShowModal()
	
	def cur_kb_calc(self, event):
		Im1 = float(self.m_cur_m1_text.GetValue())
		Ir1 = float(self.m_cur_r1_text.GetValue())
		Im2 = float(self.m_cur_m2_text.GetValue())
		Ir2 = float(self.m_cur_r2_text.GetValue())
		print Im1, Ir1, Im2, Ir2
		
		# Ir = k*Im + b
		if Im2 > Im1 and Ir2 > Ir1 :
			tmp_Im = Im2 - Im1
			tmp_Ir = Ir2 - Ir1
			K = tmp_Ir / tmp_Im
			B = Ir1 - K *Im1
			print K, B
			K = float('%.3f'%K)
			B = float('%.3f'%B)
			self.m_cur_K_text.SetValue(str(K))
			self.m_cur_B_text.SetValue(str(B))
		else:
			dlg=wx.MessageDialog(self,"测量数据不对，请检查", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
			dlg.ShowModal()
			
	#read current kb from hardware
	#response test: 1 4 2 3 e8 3 e7 4E B3
	#response fail: 1 84 1 7 D0 5C 63
	def cur_kb_read(self, event):
		if self.serial_is_open():
			#************ send **************#
			send_arr = []
			send_arr = []
			#1.dev modbus addr
			send_arr.append(modbus_dev_addr)
			#2.func code
			send_arr.append(0x04)
			#3.register addr
			send_arr.append(0x00)
			send_arr.append(0x04)
			#4. register count
			send_arr.append(0x00)
			send_arr.append(0x02)
			
			#5.CRC16
			crc_16 = crc16()
			crcvalue = crc_16.calcrc(send_arr)
			#print '%x'%crcvalue
			send_arr.append((crcvalue>>8) & 0xff)
			send_arr.append(crcvalue & 0xff)
			
			#change to bytes
			snd_bytes = ''
			for i in range(0, len(send_arr)):
				snd_bytes = snd_bytes + struct.pack("B", send_arr[i])
			self.show_snd_rcv_data(send_arr, 1)
			#send by uart
			self.Ser.flushInput()
			self.Ser.write(snd_bytes)
			
			#************ receive *************#
			ret, rcv_data = self.read_receive_data()
			if ret:
				if rcv_data[1] & func_code_invalid_mask:
					dlg=wx.MessageDialog(self,"地址或数据有误", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
					dlg.ShowModal()
				else:
					value = rcv_data[3] << 8 
					value += rcv_data[4]
					fval = float(value) / 1000
					self.m_cur_K_text.SetValue(str(fval))
					value = rcv_data[5] << 8 
					value += rcv_data[6]
					if value > 32768:
						value = value - 65536
					fval = float(value) / 1000
					self.m_cur_B_text.SetValue(str(fval))
	
	#set current kb to hardware
	#response test: 1 10 0 4 0 2 09 00
	#response fail: 1 86 2 A1 C3
	def cur_kb_set(self, event):
		if self.serial_is_open():
			#************ send **************#
			send_arr = []
			#1.dev modbus addr
			send_arr.append(modbus_dev_addr)
			#2.func code
			send_arr.append(0x10)
			#3.register addr
			send_arr.append(0x00)
			send_arr.append(0x04)
			#4. register count
			send_arr.append(0x00)
			send_arr.append(0x02)
			#5. register data len
			send_arr.append(0x04)
			
			#6-1.cur K value
			fk = float(self.m_cur_K_text.GetValue()) * 1000
			k = int(fk)
			send_arr.append((k>>8) & 0xff)
			send_arr.append(k & 0xff)
			#6-2.cur B value
			fb = float(self.m_cur_B_text.GetValue()) * 1000
			b = int(fb)
			send_arr.append((b>>8) & 0xff)
			send_arr.append(b & 0xff)
			print k ,b
			'''
			if k > 1500 or b > 1000:
				dlg=wx.MessageDialog(self,"k<=1500, b<=1000", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
				dlg.ShowModal()
				return None
			'''
			#7.CRC16
			crc_16 = crc16()
			crcvalue = crc_16.calcrc(send_arr)
			#print '%x'%crcvalue
			send_arr.append((crcvalue>>8) & 0xff)
			send_arr.append(crcvalue & 0xff)
			
			#change to bytes
			bytes = ''
			for i in range(0, len(send_arr)):
				bytes = bytes + struct.pack("B", send_arr[i])
			self.show_snd_rcv_data(send_arr, 1)
			#send by uart
			self.Ser.flushInput()
			self.Ser.write(bytes)
			
			#************ receive response *************#
			ret, rcv_data = self.set_send_response()
			if ret and rcv_data[1] & func_code_invalid_mask:
				dlg=wx.MessageDialog(self,"地址或数据有误", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
				dlg.ShowModal()
		
	#read vol reference from hardware
	#response test: 1 4 1 7 D0 9C 4A
	#response fail: 1 84 1 7 D0 5C 63
	def vol_ref_read(self, event):
		if self.serial_is_open():
			#************ send **************#
			send_arr = []
			#1.dev modbus addr
			send_arr.append(modbus_dev_addr)
			#2.func code
			send_arr.append(0x04)
			#3.register addr
			send_arr.append(0x00)
			send_arr.append(0x01)
			#4.register count
			send_arr.append(0x00)
			send_arr.append(0x01)
			
			#5.CRC16
			crc_16 = crc16()
			crcvalue = crc_16.calcrc(send_arr)
			#print '%x'%crcvalue
			send_arr.append((crcvalue>>8) & 0xff)
			send_arr.append(crcvalue & 0xff)
			
			#change to bytes
			snd_bytes = ''
			for i in range(0, len(send_arr)):
				snd_bytes = snd_bytes + struct.pack("B", send_arr[i])
			self.show_snd_rcv_data(send_arr, 1)
			#send by uart
			self.Ser.flushInput()
			self.Ser.write(snd_bytes)
			
			#************ receive *************#
			ret, rcv_data = self.read_receive_data()
			if ret:
				if rcv_data[1] & func_code_invalid_mask:
					dlg=wx.MessageDialog(self,"地址或数据有误", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
					dlg.ShowModal()
				else:
					value = rcv_data[3] << 8 
					value += rcv_data[4]
					self.m_vol_ref_text.SetValue(str(value))
		
	#set vol reference to hardware
	#response test: 1 6 0 1 7 D0 A6 DB
	#response fail: 1 86 2 A1 C3
	def vol_ref_set(self, event):
		if self.serial_is_open():
			#************ send **************#
			send_arr = []
			#1.dev modbus addr
			send_arr.append(modbus_dev_addr)
			#2.func code
			send_arr.append(0x06)
			#3.register addr
			send_arr.append(0x00)
			send_arr.append(0x01)
			
			#4.vol ref value
			vol_ref = int(self.m_vol_ref_text.GetValue(),10)
			if vol_ref > 3300:
				dlg=wx.MessageDialog(self,"电压<=3300", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
				dlg.ShowModal()
				return None
			send_arr.append((vol_ref>>8) & 0xff)
			send_arr.append(vol_ref & 0xff)
			
			#5.CRC16
			crc_16 = crc16()
			crcvalue = crc_16.calcrc(send_arr)
			#print '%x'%crcvalue
			send_arr.append((crcvalue>>8) & 0xff)
			send_arr.append(crcvalue & 0xff)
			
			#change to bytes
			bytes = ''
			for i in range(0, len(send_arr)):
				bytes = bytes + struct.pack("B", send_arr[i])
			self.show_snd_rcv_data(send_arr, 1)
			#send by uart
			self.Ser.flushInput()
			self.Ser.write(bytes)
			
			#************ receive response *************#
			ret, rcv_data = self.set_send_response()
			if ret and rcv_data[1] & func_code_invalid_mask:
				dlg=wx.MessageDialog(self,"地址或数据有误", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
				dlg.ShowModal()
			
		
########################## Run the program ############################
if __name__ == "__main__":
	app = wx.App()
	frame = serial_fram_ui()
	frame.Show()
	app.MainLoop()