#include "SimpleZipperUI.h"
#include "SimpleZipper.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPushButton>

SimpleZipperUI::SimpleZipperUI(QWidget *parent)
    : QWidget(parent)
{
    // Create "Select file to zip" button
    QPushButton* zipFileButton = new QPushButton("Select file to zip");
    connect(zipFileButton, &QPushButton::clicked, this, &SimpleZipperUI::selectFileToZip);

    // Create "Select folder to zip" button
    QPushButton * zipFolderButton = new QPushButton("Select folder to zip");
    connect(zipFolderButton, &QPushButton::clicked, this, &SimpleZipperUI::selectFolderToZip);

    // Create "Select file to unzip" button
    QPushButton* unzipButton = new QPushButton("Select file to unzip");
    connect(unzipButton, &QPushButton::clicked, this, &SimpleZipperUI::selectFileToUnzip);

    // Add buttons to layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(zipFileButton);
    layout->addWidget(zipFolderButton);
    layout->addWidget(unzipButton);
    setLayout(layout);
    this->setMinimumWidth(300);
}

SimpleZipperUI::~SimpleZipperUI()
{
}

void SimpleZipperUI::selectFileToZip()
{
    // Prompt user to select a file to zip
    QString file = QFileDialog::getOpenFileName(this, tr("Select File"), "", tr("All Files (*.*)"));

    // Zip file using SimpleZipper
    if (!file.isEmpty()) {
        SimpleZipper::zipFile(file);
    }
}

void SimpleZipperUI::selectFolderToZip()
{
    // Prompt user to select a folder to zip
    QString folder = QFileDialog::getExistingDirectory(this, tr("Select Folder to Zip"));

    // Zip folder using SimpleZipper
    if (!folder.isEmpty()) {
        SimpleZipper::zipFolder(folder);
    }
}

void SimpleZipperUI::selectFileToUnzip()
{
    // Prompt user to select a zip file to unzip
    QString zipFile = QFileDialog::getOpenFileName(this, tr("Select Zip File"), "", tr("Zip Files (*.zip)"));

    // Unzip file using SimpleZipper
    if (!zipFile.isEmpty()) {
        SimpleZipper::unzipFile(zipFile);
    }
}
