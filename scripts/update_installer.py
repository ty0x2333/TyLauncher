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