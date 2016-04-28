
# sources for the tool

sources = [
		'dataacquisitionthread.cpp',
		'main.cpp',
		'mainwindow.cpp',
		'vnalibrary.cpp',
		]


# Required (ubuntu) packages:
#  - qttools5-dev-tools
#  - qtdeclarative5-dev


Import('env libavmu')
env = env.Clone()
env.Tool('scons_qt5')

qtEnv['QT5DIR'] = '/usr/local/Trolltech/Qt-5.2.3'
qtEnv['ENV']['PKG_CONFIG_PATH'] = '/usr/local/Trolltech/Qt-5.2.3/lib/pkgconfig'

flags = {

	'CPPPATH' : ['/usr/include/qt5/QTWidgets',
					'/usr/include/qt5/QtCore',
					'/usr/include/qt5',
					"../vnadll"
					]

}


env.MergeFlags(flags)

built_lib = env.SharedLibrary("libvna", source = sources+libavmu)
Return('built_lib')

