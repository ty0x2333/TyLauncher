#include "appconfigdialog.h"
#include "ui_appconfigdialog.h"
#include "dynamicdata.h"
#include "model/option.h"
#include "datasettings.h"
#include "TyLog_Qt.h"
#include <QAbstractButton>
#include "utils/uiutils.h"

#define KEY_PROPERTY_CHECKED "checked"

#define TITILE_RESET_MSG_BOX "Reset preferences?"

#define CONTENT_RESET_MSG_BOX "This action will reset all your preferences (in all tabs) to default values.<br /><br />"\
    "Do you really want to <strong>reset all preferences</strong>?"

AppConfigDialog::AppConfigDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppConfigDialog)
    , _options()
{
    ui->setupUi(this);
    initOptions();
    initLanguages();
    initThemes();
}

AppConfigDialog::~AppConfigDialog()
{
    delete ui;
}

void AppConfigDialog::apply()
{
    DynamicData *dynamicData = DYNAMIC_DATA;
    foreach (const QString &key, _options.keys()) {
        dynamicData->setValue(key, _options[key].value());
    }
    dynamicData->setValue(KEY_LANGUAGE, ui->comboBoxLanguage->currentData());
    dynamicData->setValue(KEY_THEME, ui->comboBoxTheme->currentData());
    dynamicData->saveAppConfig();
}

void AppConfigDialog::initOptions()
{
    _options[KEY_HOT_KEY] = Option(DEFAULT_HOT_KEY, "keySequence", ui->hotKeySequenceEdit);
    _options[KEY_HOT_KEY].setValue(DYNAMIC_DATA->getGlobalShortcut());
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

void AppConfigDialog::initThemes()
{
    const QString currentTheme = DYNAMIC_DATA->getTheme();
    QStringList list = DYNAMIC_DATA->getThemeList();
    QSet<QString> themes;
    foreach ( const QString &theme, list ) {

        if ( !themes.contains(theme) ) {
            themes.insert(theme);
            const int index = ui->comboBoxTheme->count();
            ui->comboBoxTheme->addItem(theme);
            ui->comboBoxTheme->setItemData(index, theme);

            if (currentTheme == theme) {
                ui->comboBoxTheme->setCurrentIndex(index);
            }
        }
    }
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
        if ( UIUtils::showQuestionMsgBox(tr(TITILE_RESET_MSG_BOX), 
                                tr(CONTENT_RESET_MSG_BOX), 
                                this) == QMessageBox::Yes){
            foreach ( const QString &key, _options.keys() ) {
                _options[key].reset();
            }
            ui->comboBoxLanguage->setCurrentIndex(0);
        }
        break;
    default:
        return;
    }
}
