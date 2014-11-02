import os


###################################### App Target

def PhonyTarget(target, action):
	phony = Environment(ENV = os.environ,
						BUILDERS = { 'phony' : Builder(action = action) })
	AlwaysBuild(phony.phony(target = target, source = 'SConstruct'))

PhonyTarget('GAME_BUILD', 'cd build/osx/;xcodebuild -scheme Game build CONFIGURATION_BUILD_DIR="../../bin";cd ../../')

PhonyTarget('GAME_RUN', 'open ./bin/Game.app')
