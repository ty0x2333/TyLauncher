from application_configuration import *
import re
__author__ = 'luckytianyiyan@gmail.com'
# Settings
CONGIG_FILE = '../src/config.json'
RC_FILE = '../src/TyLauncher.rc'
STRING_FILE_INFO_REGEX_FORMAT = 'VALUE\s+"%s"\s*,\s+(.+)'
COPYRIGHT_REGEX = STRING_FILE_INFO_REGEX_FORMAT % ("LegalCopyright")
PRODUCT_NAME_REGEX = STRING_FILE_INFO_REGEX_FORMAT % ("ProductName")
COMPANY_NAME_REGEX = STRING_FILE_INFO_REGEX_FORMAT % ("CompanyName")
ORIGINAL_FILE_NAME_REGEX = STRING_FILE_INFO_REGEX_FORMAT % ("OriginalFilename")
FILE_VERSION_REGEX = STRING_FILE_INFO_REGEX_FORMAT % ("FileVersion")
PRODUCT_VERSION_REGEX = STRING_FILE_INFO_REGEX_FORMAT % ("ProductVersion")
FILE_DESCRIPTION_REGEX = STRING_FILE_INFO_REGEX_FORMAT % ("FileDescription")
INTERNAL_NAME_REGEX = STRING_FILE_INFO_REGEX_FORMAT % ("InternalName")

# VS_VERSION_INFO
VERSION_INFO_REGEX_FORMAT = '%s\s+(.+)'
VERSION_INFO_FILE_VERSION_REGEX = VERSION_INFO_REGEX_FORMAT % ("FILEVERSION")
VERSION_INFO_PRODUCT_VERSION = VERSION_INFO_REGEX_FORMAT % ("PRODUCTVERSION")


def update_rc():
    # Read
    try:
        rc_file = open(RC_FILE, 'r')
        rc_content = rc_file.read( )
    finally:
        rc_file.close()

    # Process
    rc_content = process_rc(rc_content)

    # Write
    try:
        rc_file = open(RC_FILE, 'w')
        rc_file.write(rc_content)
    finally:
        rc_file.close()


def process_rc(rc_content):
    config = ApplicationConfiguration(CONGIG_FILE)
    regexs = [
        # BLOCK "StringFileInfo"
        PRODUCT_NAME_REGEX,
        COPYRIGHT_REGEX,
        COMPANY_NAME_REGEX,
        ORIGINAL_FILE_NAME_REGEX,
        FILE_VERSION_REGEX,
        PRODUCT_VERSION_REGEX,
        FILE_DESCRIPTION_REGEX,
        INTERNAL_NAME_REGEX,
        # VS_VERSION_INFO
        VERSION_INFO_FILE_VERSION_REGEX,
        VERSION_INFO_PRODUCT_VERSION
    ]
    values = [
        # BLOCK "StringFileInfo"
        '"' + config.product_name + '"',
        '"' + config.copyright + '"',
        '"' + config.company_name + '"',
        '"' + config.original_file_name + '"',
        '"' + config.version + '\\0"',
        '"' + config.version + '\\0"',
        '"' + config.description + '"',
        '"' + config.internal_name + '"',
        # VS_VERSION_INFO
        config.version.replace('.', ','),
        config.version.replace('.', ',')
    ]

    content = rc_content
    for index, reg in enumerate(regexs):
        pattern = re.compile(reg)
        pos = pattern.search(content).regs[-1]
        content = content[:pos[0]] + values[index] + content[pos[1]:]

    return content

if __name__ == '__main__':
    print '--- update windows rc file ---'

    update_rc()

    print 'success update windows rc file.'
