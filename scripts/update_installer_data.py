import shutil
import os
from optparse import OptionParser
__author__ = 'luckytianyiyan@gmail.com'

INSTALLER_DIR_32_BIT = '..\\installer_src\\TyLauncherInstaller_i386'
INSTALLER_DIR_64_BIT = '..\\installer_src\\TyLauncherInstaller_x86_64'


def installer_packages_dir(installer_dir):
    return os.path.join(installer_dir, 'packages')


def installer_package_data_dir(installer_dir, package_name):
    return os.path.join(installer_packages_dir(installer_dir), '%s\\data' % package_name)


def clean_all_data(installer_dir):
    package_list_dir = installer_packages_dir(installer_dir)
    for package in os.listdir(package_list_dir):
        print '- Clean %s Package Data -' % package
        package_data_dir = installer_package_data_dir(installer_dir, package)
        print 'package_data_dir: %s' % package_data_dir

        if not os.path.exists(package_data_dir):
            os.makedirs(package_data_dir)
        else:
            for item in os.listdir(package_data_dir):
                filename = os.path.join(package_data_dir, item)
                if os.path.isdir(filename):
                    shutil.rmtree(filename)
                elif os.path.isfile(filename):
                    os.remove(filename)


def copy_common(package_dir, installer_dir, package_name='com.tianyiyan.tylauncher'):
    print '- Copy %s Package Data -' % package_name
    package_data_dir = installer_package_data_dir(installer_dir, package_name)

    theme_dir = os.path.join(package_dir, 'theme')
    language_dir = os.path.join(package_dir, 'language')
    target_theme_dir = os.path.join(package_data_dir, 'theme')
    target_language_dir = os.path.join(package_data_dir, 'language')

    print 'Theme Path: %s' % theme_dir
    print 'Target Theme Path: %s' % target_theme_dir
    print 'Language Path: %s' % language_dir
    print 'Target Language Path: %s' % target_language_dir

    if os.path.exists(target_theme_dir):
        print 'Delete exists theme dir'
        shutil.rmtree(target_theme_dir)
    shutil.copytree(theme_dir, target_theme_dir)
    print 'copy %s to %s' % (theme_dir, target_theme_dir)

    if os.path.exists(target_language_dir):
        print 'Delete exists language dir'
        shutil.rmtree(target_language_dir)
    shutil.copytree(language_dir, target_language_dir)
    print 'copy %s to %s' % (language_dir, target_language_dir)


def copy_other_files(package_dir, installer_dir, package_name):
    print '- Copy %s Package Data -' % package_name
    package_data_dir = installer_package_data_dir(installer_dir, package_name)
    for item in os.listdir(package_dir):
        filename = os.path.join(package_dir, item)
        if os.path.isfile(filename):
            target_file_name = os.path.join(package_data_dir, item)
            if os.path.exists(target_file_name):
                print 'Delete exists file: %s' % target_file_name
                os.remove(target_file_name)
            shutil.copy(filename, target_file_name)
            print 'copy %s to %s' % (filename, target_file_name)
        elif os.path.isdir(filename) and item != 'theme' and item != 'language':
            target_dir = os.path.join(package_data_dir, item)
            if os.path.exists(target_dir):
                print 'Delete exists dir: %s' % target_dir
                shutil.rmtree(target_dir)
            shutil.copytree(filename, target_dir)
            print 'copy %s to %s' % (filename, target_dir)


def get_args():
    usage = '''
    %prog [options] arg
    Update TyLauncher Installer Data
    '''
    parser = OptionParser(usage)
    parser.add_option("--32bit", dest="i386", help="TyLauncher 32 bit package directory")
    parser.add_option("--64bit", dest="x86_64", help="TyLauncher 64 bit package directory")
    parser.add_option("--clean", action="store_true", dest="clean", help="clean all installer data")
    return parser.parse_args()


def main():
    current_path = os.getcwd()
    installer_32_bit_path = os.path.join(current_path, INSTALLER_DIR_32_BIT)
    installer_64_bit_path = os.path.join(current_path, INSTALLER_DIR_64_BIT)

    (options, args) = get_args()

    if options.clean:
        print '\nclean installer 32 bit\n========='
        clean_all_data(installer_32_bit_path)
        print '\nclean installer 64 bit\n========='
        clean_all_data(installer_64_bit_path)

    if options.i386:
        print '\nupdate installer 32 bit\n========='
        clean_all_data(installer_32_bit_path)
        copy_common(options.i386, installer_32_bit_path)
        copy_other_files(options.i386, installer_32_bit_path, 'com.tianyiyan.tylauncher.i386')

    if options.x86_64:
        print '\nupdate installer 64 bit\n========='
        clean_all_data(installer_64_bit_path)
        copy_common(options.x86_64, installer_64_bit_path)
        copy_other_files(options.x86_64, installer_64_bit_path, 'com.tianyiyan.tylauncher.x86_64')

if __name__ == '__main__':
    main()

