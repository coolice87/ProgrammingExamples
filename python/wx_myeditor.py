#---------------------------------------------------------------------
#Name:   a simple editor
#Author:    Sharedelin
#Created:   2016/08/04
#Licence:   
#---------------------------------------------------------------------

#import kinds of lib
import wx
print wx.version()

#################### set the file filter ##############################
loadwildcard1 = "All files (*.*)|*.*|" \
            "Python source (*.py; *.pyc)|*.py;*.pyc"
savewildcard2 = "tex files (*.txt)|*.txt|" \
				"Python source (*.py; *.pyc)|*.py;*.pyc|"\
				"All files (*.*)|*.*"
			
######################### class and function #########################
class my_frame(wx.Frame):
	#init
	def __init__(self):
		wx.Frame.__init__(self, None, wx.ID_ANY, "simple editor", pos =(-1,-1), size =(820, 335))
		
		#def the global variance
		global filepathname,contents
		
		#layout the Frame
		panel = wx.Panel(self, wx.ID_ANY)
		filepathname = wx.TextCtrl(panel)
		loadBtn = wx.Button(panel, label='Open')
		saveBtn = wx.Button(panel, label='Save')
		saveAsBtn = wx.Button(panel, label='Save As')
		
		contents = wx.TextCtrl(panel, style=wx.TE_MULTILINE|wx.HSCROLL)
		
		hbox = wx.BoxSizer(wx.HORIZONTAL)
		hbox.Add(filepathname, proportion=1, flag=wx.EXPAND)
		hbox.Add(loadBtn, proportion = 0, flag=wx.LEFT, border=5)
		hbox.Add(saveBtn, proportion = 0, flag=wx.LEFT, border=5)
		hbox.Add(saveAsBtn, proportion = 0, flag=wx.LEFT, border=5)

		vbox = wx.BoxSizer(wx.VERTICAL)
		vbox.Add(hbox, proportion=0, flag=wx.EXPAND|wx.ALL, border=5)
		vbox.Add(contents, proportion=1, flag=wx.EXPAND|wx.LEFT|wx.BOTTOM|wx.RIGHT, border=5)

		#panel.SetSizer(vbox)
		panel.SetSizerAndFit(vbox)
		
		#bind the button event
		loadBtn.Bind(wx.EVT_BUTTON, self.loadfile)
		saveBtn.Bind(wx.EVT_BUTTON, self.savefile)
		saveAsBtn.Bind(wx.EVT_BUTTON, self.saveasfile)
	
	#load and open file
	def loadfile(self, event):
		'''
		create and show the open dialg
		'''
		dlg = wx.FileDialog(self, 
			message="Choose a file",
			defaultFile="",
			wildcard=loadwildcard1,
			style=wx.OPEN | wx.MULTIPLE | wx.CHANGE_DIR
			)
		if dlg.ShowModal() == wx.ID_OK:
			tmp=""
			paths = dlg.GetPaths()
			#print "You chose the following file(s):"
			for path in paths:
				tmp=tmp+path
			#set the value of TextCtrl[filepathname]
			filepathname.SetValue(tmp)
			#set the value to the TextCtrl[contents]
			file=open(filepathname.GetValue())
			contents.SetValue(file.read())
			file.close()
		dlg.Destroy()
	
	#save contents to file
	def savefile(self, event):
		if filepathname.GetValue() == "":
			dlg=wx.MessageDialog(self,"don't have a file!", "MessageDialog", wx.OK|wx.ICON_INFORMATION)
			dlg.ShowModal()
		else:
			file = open(filepathname.GetValue(), 'w')
			file.write(contents.GetValue())
			file.close()
		
	#save contents to an anthor file
	def saveasfile(self, event):
		dlg = wx.FileDialog(self, 
			message="Choose a file",
			defaultFile="",
			wildcard=savewildcard2,
			style=wx.SAVE
			)
		if dlg.ShowModal() == wx.ID_OK:
			tmp = ""
			paths = dlg.GetPaths()
			for path in paths:
				tmp = tmp+path
			file=open(tmp,'w')
			file.write(contents.GetValue())
			file.close()
			filepathname.SetValue(tmp)
		dlg.Destroy()
		
########################## Run the program ############################
if __name__ == "__main__":
	app = wx.App()
	frame = my_frame()
	frame.Show()
	app.MainLoop()