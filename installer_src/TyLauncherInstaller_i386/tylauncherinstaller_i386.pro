TEMPLATE = aux

INSTALLER = TyLauncherInstaller_i386

INPUT = $$PWD/config/config.xml $$PWD/packages
TyLauncherInstaller.input = INPUT
TyLauncherInstaller.output = $$INSTALLER
TyLauncherInstaller.commands = ../../bin/binarycreator -c $$PWD/config/config.xml -p $$PWD/packages ${QMAKE_FILE_OUT}
TyLauncherInstaller.CONFIG += target_predeps no_link combine

QMAKE_EXTRA_COMPILERS += TyLauncherInstaller

#OTHER_FILES = README
