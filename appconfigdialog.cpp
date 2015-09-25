#include "appconfigdialog.h"
#include "ui_appconfigdialog.h"
#include "dynamicdata.h"
AppConfigDialog::AppConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AppConfigDialog)
{
    ui->setupUi(this);
    initLanguages();
    ui->checkBoxAlwaysOnTop->setChecked(DYNAMIC_DATA->getAlwaysOnTop());
}

AppConfigDialog::~AppConfigDialog()
{
    delete ui;
}

void AppConfigDialog::initLanguages()
{
    const QString currentLocale = QLocale().name();
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
