#include "appconfigdialog.h"
#include "ui_appconfigdialog.h"
#include "dynamicdata.h"
#include "model/option.h"
#include "datasettings.h"

#define KEY_PROPERTY_CHECKED "checked"

AppConfigDialog::AppConfigDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppConfigDialog)
    , _options()
{
    ui->setupUi(this);
    initOptions();
    initLanguages();
    ui->checkBoxAlwaysOnTop->setChecked(DYNAMIC_DATA->getAlwaysOnTop());
}

AppConfigDialog::~AppConfigDialog()
{
    delete ui;
}

void AppConfigDialog::initOptions()
{
    _options[KEY_ALWAYS_ON_TOP] = Option(DEFAULT_ALWAYS_ON_TOP, KEY_PROPERTY_CHECKED, ui->checkBoxAlwaysOnTop);
}

void AppConfigDialog::initLanguages()
{
    const QString currentLocale = DYNAMIC_DATA->getLanguage();
    bool currentLocaleFound = false;
    QSet<QString> languages;
    
    QStringList list = DYNAMIC_DATA->getLanguageList();
    
    foreach ( const QString &locale, list ) {
        const QString language = QLocale(locale).nativeLanguageName();

        if ( !languages.contains(language) ) {
            languages.insert(language);
            const int index = ui->comboBoxLanguage->count();
            ui->comboBoxLanguage->addItem(language);
            ui->comboBoxLanguage->setItemData(index, locale);

            if (!currentLocaleFound) {
                currentLocaleFound = (locale == currentLocale);
                if (currentLocaleFound || currentLocale.startsWith(locale + "_"))
                    ui->comboBoxLanguage->setCurrentIndex(index);
            }
        }
    }

    ui->comboBoxLanguage->setSizeAdjustPolicy(QComboBox::AdjustToContents);
}
