import os
__author__ = 'luckytianyiyan@gmail.com'

print 'Step.1 update installer images'
print '--- start script', 'update_installer_images.bat', '... ---'
os.system('update_installer_images.bat')
print '--- script', 'update_installer_images.bat', 'finished ---'

print 'Step.2 update installer configurations'
print '--- start script', 'update_installer_config.py', '... ---'
os.system('python update_installer_config.py')
print '--- script', 'update_installer_config.py', 'finished ---'

print 'Setp.3 update installer data'
print '--- start script', 'update_installer_data.py', '... ---'
i386_package_dir = raw_input('Input TyLauncher 32 bit package directory:')
x86_64_package_dir = raw_input('Input TyLauncher 64 bit package directory:')

script = 'python update_installer_data.py'

if len(i386_package_dir) > 0:
    script += ' --32bit %s' % i386_package_dir

if len(x86_64_package_dir) > 0:
    script += ' --64bit %s' % x86_64_package_dir
os.system(script)
print '--- script', 'update_installer_data.py', 'finished ---'