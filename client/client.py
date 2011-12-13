# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'client.ui'
#
# Created: Mon Dec 12 20:22:39 2011
# by: PyQt4 UI code generator 4.8.6
#
# WARNING! All changes made in this file will be lost!

import socket
from PyQt4 import QtCore, QtGui

HOST = socket.gethostname()
PORT = 0x1234
MSGSIZE = 8192

s = None

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName(_fromUtf8("Form"))
        Form.resize(1090, 640)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(Form.sizePolicy().hasHeightForWidth())
        Form.setSizePolicy(sizePolicy)
        Form.setWindowTitle(QtGui.QApplication.translate("Form", "Clever Name", None, QtGui.QApplication.UnicodeUTF8))
        Form.setAutoFillBackground(False)
        self.verticalLayout = QtGui.QVBoxLayout(Form)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.tabWidget = QtGui.QTabWidget(Form)
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Ignored)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.tabWidget.sizePolicy().hasHeightForWidth())
        self.tabWidget.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.tabWidget.setFont(font)
        self.tabWidget.setFocusPolicy(QtCore.Qt.TabFocus)
        self.tabWidget.setObjectName(_fromUtf8("tabWidget"))
        self.tab = QtGui.QWidget()
        self.tab.setObjectName(_fromUtf8("tab"))
        self.changeTable = QtGui.QTableWidget(self.tab)
        self.changeTable.setGeometry(QtCore.QRect(0, 0, 1061, 441))
        self.changeTable.setRowCount(16)
        self.changeTable.setColumnCount(10)
        self.changeTable.setObjectName(_fromUtf8("changeTable"))
        self.go = QtGui.QPushButton(self.tab)
        self.go.setGeometry(QtCore.QRect(430, 210, 191, 20))
        self.go.setText(QtGui.QApplication.translate("Form", "Load Portfolio", None, QtGui.QApplication.UnicodeUTF8))
        self.go.setObjectName(_fromUtf8("go"))
        self.clientTime = QtGui.QLabel(self.tab)
        self.clientTime.setGeometry(QtCore.QRect(1, 535, 88, 17))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.clientTime.setFont(font)
        self.clientTime.setText(QtGui.QApplication.translate("Form", "Client Time:", None, QtGui.QApplication.UnicodeUTF8))
        self.clientTime.setObjectName(_fromUtf8("clientTime"))
        self.widget = QtGui.QWidget(self.tab)
        self.widget.setGeometry(QtCore.QRect(2, 564, 1041, 19))
        self.widget.setObjectName(_fromUtf8("widget"))
        self.horizontalLayout = QtGui.QHBoxLayout(self.widget)
        self.horizontalLayout.setMargin(0)
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.serverTime = QtGui.QLabel(self.widget)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.serverTime.setFont(font)
        self.serverTime.setText(QtGui.QApplication.translate("Form", "Server Time:", None, QtGui.QApplication.UnicodeUTF8))
        self.serverTime.setObjectName(_fromUtf8("serverTime"))
        self.horizontalLayout.addWidget(self.serverTime)
        self.realTime = QtGui.QLabel(self.widget)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.realTime.setFont(font)
        self.realTime.setText(QtGui.QApplication.translate("Form", "Real:", None, QtGui.QApplication.UnicodeUTF8))
        self.realTime.setObjectName(_fromUtf8("realTime"))
        self.horizontalLayout.addWidget(self.realTime)
        self.userTime = QtGui.QLabel(self.widget)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.userTime.setFont(font)
        self.userTime.setText(QtGui.QApplication.translate("Form", "User:", None, QtGui.QApplication.UnicodeUTF8))
        self.userTime.setObjectName(_fromUtf8("userTime"))
        self.horizontalLayout.addWidget(self.userTime)
        self.systemTime = QtGui.QLabel(self.widget)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.systemTime.setFont(font)
        self.systemTime.setText(QtGui.QApplication.translate("Form", "System:", None, QtGui.QApplication.UnicodeUTF8))
        self.systemTime.setObjectName(_fromUtf8("systemTime"))
        self.horizontalLayout.addWidget(self.systemTime)
        self.userSystemTime = QtGui.QLabel(self.widget)
        self.userSystemTime.setText(QtGui.QApplication.translate("Form", "User + System:", None, QtGui.QApplication.UnicodeUTF8))
        self.userSystemTime.setObjectName(_fromUtf8("userSystemTime"))
        self.horizontalLayout.addWidget(self.userSystemTime)
        self.widget1 = QtGui.QWidget(self.tab)
        self.widget1.setGeometry(QtCore.QRect(1, 450, 1041, 19))
        self.widget1.setObjectName(_fromUtf8("widget1"))
        self.horizontalLayout_2 = QtGui.QHBoxLayout(self.widget1)
        self.horizontalLayout_2.setMargin(0)
        self.horizontalLayout_2.setObjectName(_fromUtf8("horizontalLayout_2"))
        self.varTotal = QtGui.QLabel(self.widget1)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.varTotal.setFont(font)
        self.varTotal.setText(QtGui.QApplication.translate("Form", "VaR - Total:", None, QtGui.QApplication.UnicodeUTF8))
        self.varTotal.setObjectName(_fromUtf8("varTotal"))
        self.horizontalLayout_2.addWidget(self.varTotal)
        self.vt1 = QtGui.QLabel(self.widget1)
        self.vt1.setText(_fromUtf8(""))
        self.vt1.setTextFormat(QtCore.Qt.PlainText)
        self.vt1.setObjectName(_fromUtf8("vt1"))
        self.horizontalLayout_2.addWidget(self.vt1)
        self.vt2 = QtGui.QLabel(self.widget1)
        self.vt2.setText(_fromUtf8(""))
        self.vt2.setTextFormat(QtCore.Qt.PlainText)
        self.vt2.setObjectName(_fromUtf8("vt2"))
        self.horizontalLayout_2.addWidget(self.vt2)
        self.vt3 = QtGui.QLabel(self.widget1)
        self.vt3.setText(_fromUtf8(""))
        self.vt3.setTextFormat(QtCore.Qt.PlainText)
        self.vt3.setObjectName(_fromUtf8("vt3"))
        self.horizontalLayout_2.addWidget(self.vt3)
        self.widget2 = QtGui.QWidget(self.tab)
        self.widget2.setGeometry(QtCore.QRect(1, 507, 1041, 19))
        self.widget2.setObjectName(_fromUtf8("widget2"))
        self.horizontalLayout_3 = QtGui.QHBoxLayout(self.widget2)
        self.horizontalLayout_3.setMargin(0)
        self.horizontalLayout_3.setObjectName(_fromUtf8("horizontalLayout_3"))
        self.varCS = QtGui.QLabel(self.widget2)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.varCS.setFont(font)
        self.varCS.setText(QtGui.QApplication.translate("Form", "VaR - Credit Spread:", None, QtGui.QApplication.UnicodeUTF8))
        self.varCS.setObjectName(_fromUtf8("varCS"))
        self.horizontalLayout_3.addWidget(self.varCS)
        self.vc1 = QtGui.QLabel(self.widget2)
        self.vc1.setText(_fromUtf8(""))
        self.vc1.setTextFormat(QtCore.Qt.PlainText)
        self.vc1.setObjectName(_fromUtf8("vc1"))
        self.horizontalLayout_3.addWidget(self.vc1)
        self.vc2 = QtGui.QLabel(self.widget2)
        self.vc2.setText(_fromUtf8(""))
        self.vc2.setTextFormat(QtCore.Qt.PlainText)
        self.vc2.setObjectName(_fromUtf8("vc2"))
        self.horizontalLayout_3.addWidget(self.vc2)
        self.vc3 = QtGui.QLabel(self.widget2)
        self.vc3.setText(_fromUtf8(""))
        self.vc3.setTextFormat(QtCore.Qt.PlainText)
        self.vc3.setObjectName(_fromUtf8("vc3"))
        self.horizontalLayout_3.addWidget(self.vc3)
        self.widget3 = QtGui.QWidget(self.tab)
        self.widget3.setGeometry(QtCore.QRect(1, 479, 1041, 19))
        self.widget3.setObjectName(_fromUtf8("widget3"))
        self.horizontalLayout_4 = QtGui.QHBoxLayout(self.widget3)
        self.horizontalLayout_4.setMargin(0)
        self.horizontalLayout_4.setObjectName(_fromUtf8("horizontalLayout_4"))
        self.varIR = QtGui.QLabel(self.widget3)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.varIR.setFont(font)
        self.varIR.setText(QtGui.QApplication.translate("Form", "VaR - Interest Rate:", None, QtGui.QApplication.UnicodeUTF8))
        self.varIR.setObjectName(_fromUtf8("varIR"))
        self.horizontalLayout_4.addWidget(self.varIR)
        self.vi1 = QtGui.QLabel(self.widget3)
        self.vi1.setText(_fromUtf8(""))
        self.vi1.setTextFormat(QtCore.Qt.PlainText)
        self.vi1.setObjectName(_fromUtf8("vi1"))
        self.horizontalLayout_4.addWidget(self.vi1)
        self.vi2 = QtGui.QLabel(self.widget3)
        self.vi2.setText(_fromUtf8(""))
        self.vi2.setTextFormat(QtCore.Qt.PlainText)
        self.vi2.setObjectName(_fromUtf8("vi2"))
        self.horizontalLayout_4.addWidget(self.vi2)
        self.vi3 = QtGui.QLabel(self.widget3)
        self.vi3.setText(_fromUtf8(""))
        self.vi3.setTextFormat(QtCore.Qt.PlainText)
        self.vi3.setObjectName(_fromUtf8("vi3"))
        self.horizontalLayout_4.addWidget(self.vi3)
        self.tabWidget.addTab(self.tab, _fromUtf8(""))
        self.tab_2 = QtGui.QWidget()
        self.tab_2.setObjectName(_fromUtf8("tab_2"))
        self.riskTable = QtGui.QTableWidget(self.tab_2)
        self.riskTable.setGeometry(QtCore.QRect(0, 0, 1061, 375))
        self.riskTable.setRowCount(11)
        self.riskTable.setColumnCount(9)
        self.riskTable.setObjectName(_fromUtf8("riskTable"))
        self.layoutWidget_3 = QtGui.QWidget(self.tab_2)
        self.layoutWidget_3.setGeometry(QtCore.QRect(0, 570, 1041, 20))
        self.layoutWidget_3.setObjectName(_fromUtf8("layoutWidget_3"))
        self.horizontalLayout_5 = QtGui.QHBoxLayout(self.layoutWidget_3)
        self.horizontalLayout_5.setMargin(0)
        self.horizontalLayout_5.setObjectName(_fromUtf8("horizontalLayout_5"))
        self.serverTime_2 = QtGui.QLabel(self.layoutWidget_3)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.serverTime_2.setFont(font)
        self.serverTime_2.setText(QtGui.QApplication.translate("Form", "Server Time:", None, QtGui.QApplication.UnicodeUTF8))
        self.serverTime_2.setObjectName(_fromUtf8("serverTime_2"))
        self.horizontalLayout_5.addWidget(self.serverTime_2)
        self.realTime_2 = QtGui.QLabel(self.layoutWidget_3)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.realTime_2.setFont(font)
        self.realTime_2.setText(QtGui.QApplication.translate("Form", "Real:", None, QtGui.QApplication.UnicodeUTF8))
        self.realTime_2.setObjectName(_fromUtf8("realTime_2"))
        self.horizontalLayout_5.addWidget(self.realTime_2)
        self.userTime_2 = QtGui.QLabel(self.layoutWidget_3)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.userTime_2.setFont(font)
        self.userTime_2.setText(QtGui.QApplication.translate("Form", "User:", None, QtGui.QApplication.UnicodeUTF8))
        self.userTime_2.setObjectName(_fromUtf8("userTime_2"))
        self.horizontalLayout_5.addWidget(self.userTime_2)
        self.systemTime_2 = QtGui.QLabel(self.layoutWidget_3)
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.systemTime_2.setFont(font)
        self.systemTime_2.setText(QtGui.QApplication.translate("Form", "System:", None, QtGui.QApplication.UnicodeUTF8))
        self.systemTime_2.setObjectName(_fromUtf8("systemTime_2"))
        self.horizontalLayout_5.addWidget(self.systemTime_2)
        self.userSystemTime_2 = QtGui.QLabel(self.layoutWidget_3)
        self.userSystemTime_2.setText(QtGui.QApplication.translate("Form", "User + System:", None, QtGui.QApplication.UnicodeUTF8))
        self.userSystemTime_2.setObjectName(_fromUtf8("userSystemTime_2"))
        self.horizontalLayout_5.addWidget(self.userSystemTime_2)
        self.clientTime_2 = QtGui.QLabel(self.tab_2)
        self.clientTime_2.setGeometry(QtCore.QRect(0, 550, 1067, 17))
        font = QtGui.QFont()
        font.setBold(True)
        font.setWeight(75)
        self.clientTime_2.setFont(font)
        self.clientTime_2.setText(QtGui.QApplication.translate("Form", "Client Time:", None, QtGui.QApplication.UnicodeUTF8))
        self.clientTime_2.setObjectName(_fromUtf8("clientTime_2"))
        self.shiftUp = QtGui.QPushButton(self.tab_2)
        self.shiftUp.setGeometry(QtCore.QRect(50, 390, 325, 27))
        self.shiftUp.setText(QtGui.QApplication.translate("Form", "Shift Up 50%", None, QtGui.QApplication.UnicodeUTF8))
        self.shiftUp.setObjectName(_fromUtf8("shiftUp"))
        self.shiftDown = QtGui.QPushButton(self.tab_2)
        self.shiftDown.setGeometry(QtCore.QRect(380, 390, 325, 27))
        self.shiftDown.setText(QtGui.QApplication.translate("Form", "Shift Down 50%", None, QtGui.QApplication.UnicodeUTF8))
        self.shiftDown.setObjectName(_fromUtf8("shiftDown"))
        self.reset = QtGui.QPushButton(self.tab_2)
        self.reset.setGeometry(QtCore.QRect(710, 390, 325, 27))
        self.reset.setText(QtGui.QApplication.translate("Form", "Reset", None, QtGui.QApplication.UnicodeUTF8))
        self.reset.setObjectName(_fromUtf8("reset"))
        self.tabWidget.addTab(self.tab_2, _fromUtf8(""))
        self.verticalLayout.addWidget(self.tabWidget)
        
        self.retranslateUi(Form)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QObject.connect(self.shiftUp, QtCore.SIGNAL(_fromUtf8("clicked()")), self.shiftUpMeth)
        QtCore.QObject.connect(self.shiftDown, QtCore.SIGNAL(_fromUtf8("clicked()")), self.shiftDownMeth)
        QtCore.QObject.connect(self.reset, QtCore.SIGNAL(_fromUtf8("clicked()")), self.resetMeth)
        QtCore.QObject.connect(self.go, QtCore.SIGNAL(_fromUtf8("clicked()")), self.goMeth)
        #self.riskTable.cellChanged(self.realTime_2.hide)
        QtCore.QMetaObject.connectSlotsByName(Form)
    
    #initializes table and loads porfolio
    def goMeth(self):
        self.go.hide()
        self.initializeTable()
        self.loadPortfolio()
    
    def retranslateUi(self, Form):
        self.changeTable.setSortingEnabled(True)
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), QtGui.QApplication.translate("Form", "Daily Change", None, QtGui.QApplication.UnicodeUTF8))
        self.riskTable.setSortingEnabled(True)
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), QtGui.QApplication.translate("Form", "Risk", None, QtGui.QApplication.UnicodeUTF8))
    
    def loadPortfolio(self):
        s.send("loadticker")
        data = repr(s.recv(MSGSIZE))
        data = data.strip('\'')
        tickerdata = data.split("blah");
        row = self.loadticker(tickerdata[0])
        self.loadquality(tickerdata[1].strip(' '), row)
        self.calcInvestmentJunkBonds(row)
        
        
        s.send("loadvars")
        vardata = repr(s.recv(MSGSIZE))
        vardata = vardata.strip('\'')
        self.loadvars(vardata)
        
        s.send("loadyieldcurve")
        yielddata = repr(s.recv(MSGSIZE))
        yielddata = yielddata.strip('\'')
        self.loadYieldCurve(yielddata)
    
        s.send("loadBucketClose")
        bucketData = repr(s.recv(MSGSIZE))
        bucketData = bucketData.strip('\'')
        hedgeData = bucketData.split("blah");
        
        self.loadBucketClose(hedgeData[0])
        self.load2YrHedge(hedgeData[1].strip(' '))

            
        '''
        
           
        data = ""
        self.loadtime(data)'''
    
    def bumpCurve(self, row, col):
        if row == 10: #if change is in bumpCurve row
            #finding bucket
            bucket = "69"
            if col == 2:
                bucket = "2"
            elif col == 4:
                bucket = "5"
            elif col == 6:
                bucket = "10"
            elif col == 8:
                bucket = "30"
            
            amount = self.riskTable.item(row, col).text()
            
            msg = "bump_" + bucket + "_" + str(amount)
            print msg
            s.send(msg)
        
            bump_delta = repr(s.recv(MSGSIZE))
            bump_delta = bump_delta.strip('\'')
    
            dataArr = bump_delta.split(' ')

            row = 6
            col = 1
            i = 0
            for item in dataArr:
                if i < 8: #its the bucket info
                    self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(item))
                    col += 1
                    if i == 7: #time to move to the next row
                        row += 1
                        col = 2
                elif i < 12: #its the 2 yr hedge
                    self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(item))
                    col += 2
                i += 1
            
            #update time
            time = dataArr[12] + " " + dataArr[13] + " " + dataArr[14]
            self.loadtime(time)
    
    #resets all the data entered cells
    def resetMeth(self):
        #resetting shifted buckets and hedge
        row = 6
        col = 1
        for i in range(0, 15):
            if i < 8: #its the bucket info
                self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(''))
                col += 1
                if i == 7: #time to move to the next row
                    row += 1
                    col = 2
            elif i < 12: #its the 2 yr hedge
                self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(''))
                col += 2
            i += 1
        
        #resetting bump curve values
        temp = QtGui.QTableWidgetItem("0")
        temp.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(10, 2, temp)
        temp2 = QtGui.QTableWidgetItem("0")
        temp2.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(10, 4, temp2)
        temp3 = QtGui.QTableWidgetItem("0")
        temp3.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(10, 6, temp3)
        temp4 = QtGui.QTableWidgetItem("0")
        temp4.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(10, 8, temp4)
    
    #is called when the button is pressed
    #8. "shiftdown" - returns 15 numbers, need to parse and put in both rows, last 3 numbers are the time
    def shiftDownMeth(self):
            
        s.send("shiftdown")
        yielddown = repr(s.recv(MSGSIZE))
        yielddown = yielddown.strip('\'')
            
        dataArr = yielddown.split(' ')
        row = 6
        col = 1
        i = 0
        for item in dataArr:
            if i < 8: #its the bucket info
                self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(item))
                col += 1
                if i == 7: #time to move to the next row
                    row += 1
                    col = 2
            elif i < 12: #its the 2 yr hedge
                self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(item))
                col += 2
            i += 1
        
        #update time
        time = dataArr[12] + " " + dataArr[13] + " " + dataArr[14]
        self.loadtime(time)
    
    #is called when the button is pressed
    #8. "shiftup" - returns 15 numbers, need to parse and put in both rows, last 3 numbers are the time
    def shiftUpMeth(self):
        s.send("shiftup")
        yieldup = repr(s.recv(MSGSIZE))
        yieldup = yieldup.strip('\'')
            
        dataArr = yieldup.split(' ')
        row = 6
        col = 1
        i = 0
        for item in dataArr:
            if i < 8: #its the bucket info
                self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(item))
                col += 1
                if i == 7: #time to move to the next row
                    row += 1
                    col = 2
            elif i < 12: #its the 2 yr hedge
                self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(item))
                col += 2
            i += 1
        
        #update time
        time = dataArr[12] + " " + dataArr[13] + " " + dataArr[14]
        self.loadtime(time)
    
    #7. "loadyieldcurve" - returns 4 numbers
    def loadYieldCurve(self, data):
        dataArr = data.split(' ')
        row = 9
        col = 2
        for item in dataArr:
            temp = QtGui.QTableWidgetItem(item)
            temp.setTextAlignment(QtCore.Qt.AlignCenter)
            self.riskTable.setItem(row, col, temp)
            col += 2
    
    #6. "load2yrhedge" - returns 4 numbers to go in row
    def load2YrHedge(self, data):
        dataArr = data.split(' ')
        row = 4
        col = 2
        for item in dataArr:
            self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(item))
            col += 2
    
    #"loadbucketclosingposition" - returns 8 numbers to go in row "closing position"
    def loadBucketClose(self, data):
        dataArr = data.split(' ')
        row = 3
        col = 1
        for item in dataArr:
            self.riskTable.setItem(row, col, QtGui.QTableWidgetItem(item))
            col += 1
    
    #order of data: realTime userTime sysTime
    def loadtime(self, data):
        dataArr = data.split(' ')
        self.realTime.setText("Real: " + dataArr[0])
        self.realTime_2.setText("Real: " + dataArr[0])
        self.userTime.setText("User: " + dataArr[1])
        self.userTime_2.setText("User: " + dataArr[1])
        self.systemTime.setText("System: " + dataArr[2])
        self.systemTime_2.setText("System: " + dataArr[2])
        usT = float(dataArr[1]) + float(dataArr[2])
        self.userSystemTime.setText("User + System: " + str(usT))
        self.userSystemTime_2.setText("User + System: " + str(usT))
    
    #displays vars,
    #assumes the order is opening var total, opening var interest, opening var credit, closing total, closing interest, closing credit
    def loadvars(self, data):
        dataArr = data.split(' ')
        self.vt1.setText(dataArr[0])
        self.vi1.setText(dataArr[1])
        self.vc1.setText(dataArr[2])
        self.vt2.setText(dataArr[3])
        self.vi2.setText(dataArr[4])
        self.vc2.setText(dataArr[5])
        vt3 = float(dataArr[3]) - float(dataArr[0]);
        self.vt3.setText(str(vt3))
        vi3 = float(dataArr[4]) - float(dataArr[1]);
        self.vi3.setText(str(vi3))
        vc3 = float(dataArr[5]) - float(dataArr[2]);
        self.vc3.setText(str(vc3))
    
    #calculates investment grade and junk bonds
    def calcInvestmentJunkBonds(self, r):
        topRow = r+1
        curRow = topRow
        col = 1
        sum = 0.0
        #investment grade A through BBB
        for col in range (1, 10):
            for curRow in range(topRow, topRow+6):
                cell = self.changeTable.item(curRow, col)
                sum += float(cell.text())
            #have now summed up every item in this col
            self.changeTable.setItem(topRow+10, col, QtGui.QTableWidgetItem(str(sum)))
            sum = 0.0
        #junk c, cc, ccc
        for col in range (1, 10):
            for curRow in range(topRow+6, topRow+9):
                cell = self.changeTable.item(curRow, col)
                sum += float(cell.text())
            #have now summed up every item in this col
            self.changeTable.setItem(topRow+11, col, QtGui.QTableWidgetItem(str(sum)))
            sum = 0.0
    
    #"loadquality" - loads based of rating - need to calc intraday change and separate into investment and junk
    def loadquality(self, data, r):
        print data
        dataArr = data.split(' ')
        row = r + 1
        col = 1
        for item in dataArr:
            self.changeTable.setItem(row,col, QtGui.QTableWidgetItem(item))
            col += 1
            if col > 6:
                col = 1
                self.calculateIntraDayChange(row)
                row += 1
    
    
    #"loadticker" - Notion, Risk , LGD for opening and closing positions for each ticker, need to calculate intra-day change
    #returns the row to start at for the next process
    def loadticker(self, data):
        dataArr = data.split(' ')
        row = 2
        col = 0 #column to place data
        for item in dataArr:
            self.changeTable.setItem(row,col, QtGui.QTableWidgetItem(item))
            col += 1
            if col > 6:
                col = 0
                self.calculateIntraDayChange(row)
                row += 1
                self.changeTable.insertRow(row)
        self.changeTable.removeRow(row) #correcting extra row
        return row
    
    def calculateIntraDayChange(self, row): #calculates day's change for this row
        #notional
        n1 = self.changeTable.item(row, 1)
        n2 = self.changeTable.item(row, 4)
        n = float(n2.text()) - float(n1.text())
        self.changeTable.setItem(row, 7, QtGui.QTableWidgetItem(str(n)))
        #risk
        r1 = self.changeTable.item(row, 2)
        r2 = self.changeTable.item(row, 5)
        r = float(r2.text()) - float(r1.text())
        self.changeTable.setItem(row, 8, QtGui.QTableWidgetItem(str(r)))
        #lgd
        l1 = self.changeTable.item(row, 3)
        l2 = self.changeTable.item(row, 6)
        l = float(l2.text()) - float(l1.text())
        self.changeTable.setItem(row, 9, QtGui.QTableWidgetItem(str(l)))
    
    def initializeTable(self):
        #Setting Change Table
        #Header Row
        #Opening Pos- Closing Pos - Intra-day Change
        self.changeTable.setSpan(0, 1, 1, 3)
        self.changeTable.setSpan(0, 4, 1, 3)
        self.changeTable.setSpan(0, 7, 1, 3)
        op = QtGui.QTableWidgetItem("Opening Position")
        op.setBackgroundColor(QtGui.QColor(153,255,128))
        op.setTextAlignment(QtCore.Qt.AlignCenter)
        self.changeTable.setItem(0,1,op)
        cp = QtGui.QTableWidgetItem("Closing Position")
        cp.setBackgroundColor(QtGui.QColor(255,204,0))
        cp.setTextAlignment(QtCore.Qt.AlignCenter)
        self.changeTable.setItem(0,4,cp)
        idc = QtGui.QTableWidgetItem("Intra-day Change")
        idc.setBackgroundColor(QtGui.QColor(191,255,255))
        idc.setTextAlignment(QtCore.Qt.AlignCenter)
        self.changeTable.setItem(0,7,idc)
        #Ticker - notional - risk - lgd - x3
        ticker = QtGui.QTableWidgetItem("Ticker")
        self.changeTable.setItem(1,0,ticker)
        n1 = QtGui.QTableWidgetItem("Notional")
        self.changeTable.setItem(1,1,n1)
        r1 = QtGui.QTableWidgetItem("Risk")
        self.changeTable.setItem(1,2,r1)
        l1 = QtGui.QTableWidgetItem("LGD")
        self.changeTable.setItem(1,3,l1)
        n2 = QtGui.QTableWidgetItem("Notional")
        self.changeTable.setItem(1,4,n2)
        r2 = QtGui.QTableWidgetItem("Risk")
        self.changeTable.setItem(1,5,r2)
        l2 = QtGui.QTableWidgetItem("LGD")
        self.changeTable.setItem(1,6,l2)
        n3 = QtGui.QTableWidgetItem("Notional")
        self.changeTable.setItem(1,7,n3)
        r3 = QtGui.QTableWidgetItem("Risk")
        self.changeTable.setItem(1,8,r3)
        l3 = QtGui.QTableWidgetItem("LGD")
        self.changeTable.setItem(1,9,l3)
        
        #Header Col
        A = QtGui.QTableWidgetItem("A")
        self.changeTable.setItem(4,0,A)
        AA = QtGui.QTableWidgetItem("AA")
        self.changeTable.setItem(5,0,AA)
        AAA = QtGui.QTableWidgetItem("AAA")
        self.changeTable.setItem(6,0,AAA)
        B = QtGui.QTableWidgetItem("B")
        self.changeTable.setItem(7,0,B)
        BB = QtGui.QTableWidgetItem("BB")
        self.changeTable.setItem(8,0,BB)
        BBB = QtGui.QTableWidgetItem("BBB")
        self.changeTable.setItem(9,0,BBB)
        C = QtGui.QTableWidgetItem("C")
        self.changeTable.setItem(10,0,C)
        CC = QtGui.QTableWidgetItem("CC")
        self.changeTable.setItem(11,0,CC)
        CCC = QtGui.QTableWidgetItem("CCC")
        self.changeTable.setItem(12,0,CCC)
        
        ig = QtGui.QTableWidgetItem("Investment Grade")
        self.changeTable.setItem(14,0,ig)
        junk = QtGui.QTableWidgetItem("Junk")
        self.changeTable.setItem(15,0,junk)
        
        #Setting Risk Table
        self.riskTable.setColumnWidth(0, 150)
        #2YR - 5YR - 10YR - 30YR
        self.riskTable.setSpan(0, 1, 1, 2)
        self.riskTable.setSpan(0, 3, 1, 2)
        self.riskTable.setSpan(0, 5, 1, 2)
        self.riskTable.setSpan(0, 7, 1, 2)
        
        #Vertical Header
        closingPos = QtGui.QTableWidgetItem("Closing Position")
        closingPos.setTextAlignment(QtCore.Qt.AlignVCenter)
        self.riskTable.setItem(3, 0, closingPos)
        twoYRHedge = QtGui.QTableWidgetItem("2 YR Hedge")
        twoYRHedge.setTextAlignment(QtCore.Qt.AlignVCenter)
        self.riskTable.setItem(4, 0, twoYRHedge)
        
        shiftedPos = QtGui.QTableWidgetItem("Shifted Position")
        shiftedPos.setTextAlignment(QtCore.Qt.AlignVCenter)
        self.riskTable.setItem(6, 0, shiftedPos)
        shiftedTwoYRHedge = QtGui.QTableWidgetItem("Shifted 2 YR Hedge")
        shiftedTwoYRHedge.setTextAlignment(QtCore.Qt.AlignVCenter)
        self.riskTable.setItem(7, 0, shiftedTwoYRHedge)
        
        yc = QtGui.QTableWidgetItem("Yield Curve")
        yc.setTextAlignment(QtCore.Qt.AlignVCenter)
        self.riskTable.setItem(9, 0, yc)
        bc = QtGui.QTableWidgetItem("Bump Curve")
        bc.setTextAlignment(QtCore.Qt.AlignVCenter)
        self.riskTable.setItem(10, 0, bc)
        #Changing Background Color of Non-Changeable Slots
        bc0 = QtGui.QTableWidgetItem("")
        bc0.setBackgroundColor(QtGui.QColor(238,233,233))
        self.riskTable.setItem(10,1,bc0)
        yc0 = QtGui.QTableWidgetItem("")
        yc0.setBackgroundColor(QtGui.QColor(238,233,233))
        self.riskTable.setItem(9,1,yc0)
        gry0 = QtGui.QTableWidgetItem("")
        gry0.setBackgroundColor(QtGui.QColor(238,233,233))
        self.riskTable.setItem(10,3,gry0)
        gry1 = QtGui.QTableWidgetItem("")
        gry1.setBackgroundColor(QtGui.QColor(238,233,233))
        self.riskTable.setItem(9,3,gry1)
        gry2 = QtGui.QTableWidgetItem("")
        gry2.setBackgroundColor(QtGui.QColor(238,233,233))
        self.riskTable.setItem(10,5,gry2)
        gry3 = QtGui.QTableWidgetItem("")
        gry3.setBackgroundColor(QtGui.QColor(238,233,233))
        self.riskTable.setItem(9,5,gry3)
        gry4 = QtGui.QTableWidgetItem("")
        gry4.setBackgroundColor(QtGui.QColor(238,233,233))
        self.riskTable.setItem(10,7,gry4)
        gry5 = QtGui.QTableWidgetItem("")
        gry5.setBackgroundColor(QtGui.QColor(238,233,233))
        self.riskTable.setItem(9,7,gry5)
        #Setting Changable Slots to 0
        bc1 = QtGui.QTableWidgetItem("0")
        bc1.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(10,2,bc1)
        bc2 = QtGui.QTableWidgetItem("0")
        bc2.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(10,4,bc2)
        bc3 = QtGui.QTableWidgetItem("0")
        bc3.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(10,6,bc3)
        bc4 = QtGui.QTableWidgetItem("0")
        bc4.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(10,8,bc4)
        
        #Horizontal Header
        twoYR = QtGui.QTableWidgetItem("2 YR")
        twoYR.setBackgroundColor(QtGui.QColor(255,204,0))
        twoYR.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(0, 1, twoYR)
        
        fiveYR = QtGui.QTableWidgetItem("5 YR")
        fiveYR.setBackgroundColor(QtGui.QColor(191,255,255))
        fiveYR.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(0, 3, fiveYR)
        
        tenYR = QtGui.QTableWidgetItem("10 YR")
        tenYR.setBackgroundColor(QtGui.QColor(255,128,128))
        tenYR.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(0, 5, tenYR)
        
        thirtyYR = QtGui.QTableWidgetItem("30 YR")
        thirtyYR.setBackgroundColor(QtGui.QColor(153,255,128))
        thirtyYR.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(0, 7, thirtyYR)
        
        book = QtGui.QTableWidgetItem("Book")
        book.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,0,book)
        risk2 = QtGui.QTableWidgetItem("Risk")
        risk2.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,1,risk2)
        mv2 = QtGui.QTableWidgetItem("Market Val")
        mv2.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,2,mv2)
        risk5 = QtGui.QTableWidgetItem("Risk")
        risk5.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,3,risk5)
        mv5 = QtGui.QTableWidgetItem("Market Val")
        mv5.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,4,mv5)
        risk10 = QtGui.QTableWidgetItem("Risk")
        risk10.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,5,risk10)
        mv10 = QtGui.QTableWidgetItem("Market Val")
        mv10.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,6,mv10)
        risk30 = QtGui.QTableWidgetItem("Risk")
        risk30.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,7,risk30)
        mv30 = QtGui.QTableWidgetItem("Market Val")
        mv30.setTextAlignment(QtCore.Qt.AlignCenter)
        self.riskTable.setItem(1,8,mv30)
        QtCore.QObject.connect(self.riskTable, QtCore.SIGNAL(_fromUtf8("cellChanged(int, int)")), self.bumpCurve)

    def createGraph(self):
        # Send in data as param, OR
        #data = [17, 20, 15, 10, 7, 5, 4, 3, 2, 1, 1, 0]        
        
        # Recieve data within function 
        inputString = "-20 15 10 7 5 -4 3 2 1 1 0"
        
        import tkinter as tk  # gives tk namespace
        
        data = [int(x) for x in inputString.split()]
         
        root = tk.Tk()
        root.title("FSPwners")
        screen_width = 400
        screen_height = 700
        screen = tk.Canvas(root, width=screen_width, height=screen_height, bg= 'white')
        screen.pack()
         
        # highest y = max_data_value * y_stretch
        y_stretch = 15
        # gap between lower canvas edge and x axis
        y_gap = 350
        # stretch enough to get all data items in
        x_stretch = 10
        x_width = 20
        # gap between left canvas edge and y axis
        x_gap = 20
         
         
        for x, y in enumerate(data):
            # calculate reactangle coordinates (integers) for each bar
            x0 = x * x_stretch + x * x_width + x_gap
            y0 = screen_height - (y * y_stretch + y_gap)
            x1 = x * x_stretch + x * x_width + x_width + x_gap
            y1 = screen_height - y_gap
            # draw the bar
            print(x0, y0, x1, y1)
            screen.create_rectangle(x0, y0, x1, y1, fill="red")
            # put the y value above each bar
            screen.create_text(x0+2, y0, anchor=tk.SW, text=str(y))
         
        root.mainloop()


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Form = QtGui.QWidget()
    ui = Ui_Form()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())
    s.close();


