#include "appconfigdialog.h"
#include "ui_appconfigdialog.h"
#include "dynamicdata.h"
#include "model/option.h"
#include "datasettings.h"
#include "TyLog_Qt.h"
#include <QAbstractButton>

#define KEY_PROPERTY_CHECKED "checked"
#define KEY_PROPERTY_CURRENT_DATA "currentData"

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

void AppConfigDialog::apply()
{
    foreach (const QString &key, _options.keys()) {
        DYNAMIC_DATA->setValue(key, _options[key].value());
    }
}

void AppConfigDialog::initOptions()
{
    _options[KEY_ALWAYS_ON_TOP] = Option(DEFAULT_ALWAYS_ON_TOP, KEY_PROPERTY_CHECKED, ui->checkBoxAlwaysOnTop);
    _options[KEY_LANGUAGE] = Option(DEFAULT_LANGUAGE, KEY_PROPERTY_CURRENT_DATA, ui->comboBoxLanguage);
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

void AppConfigDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch( ui->buttonBox->buttonRole(button) ) {
    case QDialogButtonBox::ApplyRole:
        TyLogDebug("ConfigDialog Apply.");
        apply();
        break;
    case QDialogButtonBox::AcceptRole:
        TyLogDebug("ConfigDialog Accept.");
        apply();
        break;
    case QDialogButtonBox::ResetRole:
        break;
    default:
        return;
    }
}
