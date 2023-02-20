/**
 * @class   SimpleZipUI.h
 *
 * @brief   GUI for zipping and unzipping files and folders.
 *
 * @details Simple Qt GUI application with three buttons for selecting files and folders
 *          to zip and unzip using SimpleZipper.
 */

#ifndef SIMPLEZIPPERUI_H
#define SIMPLEZIPPERUI_H

#include <QWidget>
#include "SimpleZipper.h"

class SimpleZipperUI : public QWidget
{
    Q_OBJECT

public:
    SimpleZipperUI(QWidget* parent = nullptr);
    ~SimpleZipperUI();

private slots:
    /**
     * @brief Select file and zip using SimpleZipper::zipFile.
     */
    void selectFileToZip();

    /**
     * @brief Select folder and zip using SimpleZipper::zipFolder.
     */
    void selectFolderToZip();

    /**
     * @brief Select file and unzip using SimpleZipper::unzipFile.
     */
    void selectFileToUnzip();
};

#endif // SIMPLEZIPPERUI_H
