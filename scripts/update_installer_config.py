import xml.etree.ElementTree as ET
from application_configuration import *
from script_settings import *
import time
__author__ = 'luckytianyiyan@gmail.com'

INSTALLER_CONFIG_FILES = ['../installer_src/TyLauncherInstaller_i386/config/config.xml',
                         '../installer_src/TyLauncherInstaller_x86_64/config/config.xml']

INSTALLER_PACKAGE_FILES = [
    '../installer_src/TyLauncherInstaller_i386/packages/com.tianyiyan.tylauncher/meta/package.xml',
    '../installer_src/TyLauncherInstaller_i386/packages/com.tianyiyan.tylauncher.i386/meta/package.xml',
    '../installer_src/TyLauncherInstaller_x86_64/packages/com.tianyiyan.tylauncher/meta/package.xml',
    '../installer_src/TyLauncherInstaller_x86_64/packages/com.tianyiyan.tylauncher.x86_64/meta/package.xml']


def process_config(filename, config):
    tree = ET.parse(filename)
    root = tree.getroot()
    # Name
    name_elem = root.find('Name')
    name_elem.text = config.product_name
    # Version
    version_elem = root.find('Version')
    version_elem.text = config.version
    # ProductUrl
    product_URL_elem = root.find('ProductUrl')
    product_URL_elem.text = config.internal_name
    # Publisher
    publisher_elem = root.find('Publisher')
    publisher_elem.text = config.company_name
    # StartMenuDir
    start_menu_dir_elem = root.find('StartMenuDir')
    start_menu_dir_elem.text = config.product_name
    # TargetDir
    target_dir_elem = root.find('TargetDir')
    target_dir_elem.text = '@ApplicationsDir@/%s' % (config.product_name)
    tree.write(filename)


def process_package(filename, config, releaseDate):
    tree = ET.parse(filename)
    root = tree.getroot()
    # Version
    version_elem = root.find('Version')
    version_elem.text = config.version
    # ReleaseDate
    release_date__elem = root.find('ReleaseDate')
    release_date__elem.text = releaseDate
    tree.write(filename)

if __name__ == '__main__':
    config = ApplicationConfiguration(CONFIG_FILE)
    print config
    release_date = time.strftime('%Y-%m-%d', time.localtime())
    for config_file in INSTALLER_CONFIG_FILES:
        process_config(config_file, config)

    for package_file in INSTALLER_PACKAGE_FILES:
        process_package(package_file, config, release_date)

    print 'success update installer config'
