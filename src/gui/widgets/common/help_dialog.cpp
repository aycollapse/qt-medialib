#include "help_dialog.h"
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>

HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent), m_text(new QTextEdit(this)), m_buttons(new QDialogButtonBox(QDialogButtonBox::Ok, this))
{
    setWindowTitle("Help");
    resize(600, 400);

    m_text->setReadOnly(true);
    m_text->setHtml(R"(
        <h2>MediaLib — Manager</h2>
        <p>The Manager is responsible for loading and saving the library data from disk, managing the images folder, and performing import/export operations for the whole data folder.</p>
        <h3>Shortcuts</h3>
        <ul>
          <li><b>Ctrl+Q</b> — Quit</li>
          <li><b>Ctrl+F</b> — Focus search input</li>
          <li><b>Enter / Escape</b> — Exit search focus</li>
          <li><b>Ctrl+E</b> — Export library to a chosen directory</li>
          <li><b>Ctrl+I</b> — Import library from a chosen directory</li>
        </ul>
        <p>Use the "Add Media" menu to create new items. Edit items by clicking them on the home view.</p>
    )");

    connect(m_buttons, &QDialogButtonBox::accepted, this, &HelpDialog::accept);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_text);
    layout->addWidget(m_buttons);
}
