#!/usr/bin/python -B   # -B prevents writing .pyc compiled versions of each module

import sys, getopt, string

validRoutineNames = ["constants",       "touchable",            "all"]
validRoutineDescr = ["loads constants", "manipulate touchable", "write all routines"]

def printHelp():
	print ''
	print 'Usage:'
	print ''
	print 'createSystemRoutine.py -s <systemName> -r [routineNames]'
	print '[routineNames] is a vector of names separated by space'
	print ''
	print 'Example: createSystemRoutine.py -s driftChamber -r constants touchable'
	print ''
	print 'Available routines:'
	for n in range(0, len(validRoutineNames)):
		print '-', validRoutineNames[n], ':',validRoutineDescr[n]
	print ''


def parseSystem(argv):
	sysName = "none"
	try:
		opts, args = getopt.getopt(argv,"h:s:r:h")
	except getopt.GetoptError:
		printHelp()
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			printHelp()
			sys.exit()
		elif opt == "-s":
			sysName = arg
       		return sysName
	return sysName

def parseRNames(argv):
	opts, args = getopt.getopt(argv,"h:s:r")
	rNames = [""]
	for opt, arg in opts:
		if opt == "-r":
			rNames = args
			return rNames
	return rNames

def validateOptions(system, routines):
	if system == 'none':
		print ''
		print 'Error: system not given, use -s to define it'
		printHelp()
		sys.exit()
	for roname in routines:
		if not roname in validRoutineNames :
			print ''
			print 'Error: ', roname, ' is not a vaild routine name'
			printHelp()
			sys.exit()


def writeHeader(sName, routines):
	headerFileName = sName + '.h'
	headerFile = open(headerFileName, 'w')
	headerFile.write('#ifndef ' + sName.upper() + 'PLUGIN\n')
	headerFile.write('#define ' + sName.upper() + 'PLUGIN 1\n')
	headerFile.write('\n')
	headerFile.write('// gdynamic\n')
	headerFile.write('#include "gdynamic.h"\n')
	headerFile.write('\n')
	headerFile.write('// c++\n')
	headerFile.write('#include <string>\n')
	headerFile.write('using namespace std;\n')
	headerFile.write('\n')
	headerFile.write('class ' + sName + 'Plugin : public GDynamic {\n')
	headerFile.write('\n')
	headerFile.write('public:\n')
	headerFile.write('\n')
	if 'constants' in routines:
		headerFile.write('\tbool loadConstants(int runno, string variation);\n')
		headerFile.write('\n')
	
	headerFile.write('private:\n')
	headerFile.write('\n')
	headerFile.write('\t // constants definitions\n')
	headerFile.write('\n')
	headerFile.write('};\n')
	headerFile.write('\n')
	headerFile.write('extern "C" GDynamic* GDynamicFactory(void) {\n')
	headerFile.write('\treturn static_cast<GDynamic*>(new ' + sName + 'Plugin);\n')
	headerFile.write('}\n')
	headerFile.write('\n')
	headerFile.write('#endif\n')
	headerFile.write('\n')
	headerFile.close()


def writeLoadConstants(sName):
	constantsFile = open('loadConstants.cc', 'w')
	constantsFile.write('#include "' + sName + '.h"\n')
	constantsFile.write('\n')
	constantsFile.write('bool ' + sName + 'Plugin::loadConstants(int runno, string variation)\n')
	constantsFile.write('{\n')
	constantsFile.write('\n')
	constantsFile.write('\n')
	constantsFile.write('\n')
	constantsFile.write('\treturn true;\n')
	constantsFile.write('}\n')

def writeSConstruct(sName, routines):
	sconsFile = open('SConstruct', 'w')
	sconsFile.write('\n')
	sconsFile.write('\n')
	sconsFile.write('\n')
	sconsFile.write('\n')
	sconsFile.write('\n')
	sconsFile.write('\n')
	sconsFile.write('\n')
	sconsFile.write('\n')
	sconsFile.write('\n')

# parsing and writing sources
systemName = parseSystem(sys.argv[1:])
routines   = parseRNames(sys.argv[1:])

validateOptions(systemName, routines)

writeHeader(systemName, routines)

if 'constants' in routines or 'all' in routines:
	writeLoadConstants(systemName)






