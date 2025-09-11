#ifndef GUI_WIDGETS_COMMON_HELP_DIALOG_H
#define GUI_WIDGETS_COMMON_HELP_DIALOG_H

#include <QDialog>

class QTextEdit;
class QDialogButtonBox;

class HelpDialog : public QDialog {
    Q_OBJECT
public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog() override = default;

private:
    QTextEdit *m_text;
    QDialogButtonBox *m_buttons;
};

#endif // GUI_WIDGETS_COMMON_HELP_DIALOG_H
