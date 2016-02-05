import json
__author__ = 'luckytianyiyan@gmail.com'
__all__ = ["ApplicationConfiguration"]


class ApplicationConfiguration:
    def __init__(self, filename):
        try:
            config_file = file(filename)

            configs = json.load(config_file)

            application = configs['Application']

            self.internal_name = application['organizationDomain']

            self.company_name = application['organizationName']

            self.product_name = application['applicationDisplayName']

            self.original_file_name = self.product_name

            self.version = application['applicationVersion']

            self.copyright = application['copyright']

            self.description = application['applicationDescription']

        finally:
            config_file.close()

    def __str__(self):
        return str({
            'internal_name': self.internal_name,
            'company_name': self.company_name,
            'product_name': self.product_name,
            'original_file_name': self.original_file_name,
            'version': self.version,
            'copyright': self.copyright,
            'description': self.description
        })