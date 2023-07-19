#include "SimpleZipper.h"
#include "miniz.h"
#include <QFile>
#include <QIODevice>
#include <QDir>
#include <QDebug>

bool SimpleZipper::unzipFile(const QString& zipFilename)
{
    QFileInfo fileInfo(zipFilename);
    QString outputFolder = fileInfo.absolutePath() + QString("/") + fileInfo.baseName();
    return unzipFile(zipFilename, outputFolder);
}

bool SimpleZipper::unzipFile(const QString& zipFilename, const QString& outputFolder)
{
    qDebug() << "Unzipping file" << zipFilename << "to" << outputFolder;

    // Create output folder if it doesn't exist
    QDir dir(outputFolder);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Open the zip file
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));
    mz_bool result = mz_zip_reader_init_file(&zip, zipFilename.toUtf8().constData(), 0);
    if (!result) {
        qWarning() << "Failed to open zip file" << zipFilename;
        return false;
    }

    // Extract each file in the zip archive
    mz_uint numFiles = mz_zip_reader_get_num_files(&zip);
    qDebug() << "Zip file contains" << numFiles << "files";
    for (uint i = 0; i < numFiles; i++) {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(&zip, i, &file_stat)) {
            qWarning() << "Failed to get file info for file" << i << "in zip file" << zipFilename;
            mz_zip_reader_end(&zip);
            return false;
        }

        QString filename = QString::fromUtf8(file_stat.m_filename);
        QString outFile = outputFolder + "/" + filename;
        qDebug() << "Extracting" << filename;

        if (!QDir().mkpath(QFileInfo(outFile).path())) {
            qWarning() << "Failed to create directory for file" << outFile;
            mz_zip_reader_end(&zip);
            return false;
        }

        if (!mz_zip_reader_extract_to_file(&zip, i, outFile.toUtf8().constData(), 0)) {
            qWarning() << "Failed to extract file" << filename << "from zip file" << zipFilename;
            mz_zip_reader_end(&zip);
            return false;
        }
    }

    // Clean up
    mz_zip_reader_end(&zip);
    qDebug() << "Unzip complete";
    return true;
}

bool SimpleZipper::zipFile(const QString& filename)
{
    QFileInfo fileInfo(filename);
    QString zipFilename = fileInfo.absoluteDir().path() + "/" + fileInfo.baseName() + ".zip";
    return zipFile(filename, zipFilename);
}

bool SimpleZipper::zipFile(const QString& filename, const QString& zipFilename)
{
    // Determine the output zip file name and path
    QFileInfo fileInfo(filename);
    qDebug() << "Zipping file" << filename << "to" << zipFilename;

    // Open the input file
    QFile inFile(filename);
    if (!inFile.exists()) {
        qWarning() << "File" << filename << "does not exist";
        return false;
    }
    if (!inFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file" << filename << "for reading";
        return false;
    }

    // Read the contents of the input file into a QByteArray
    QByteArray buffer = inFile.readAll();

    // Create and open the output zip file
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));
    if (!mz_zip_writer_init_file(&zip, zipFilename.toUtf8().constData(), 0)) {
        qWarning() << "Failed to create output zip file" << zipFilename;
        return false;
    }

    // Add the input file contents to the zip archive
    if (!mz_zip_writer_add_mem(&zip, fileInfo.fileName().toUtf8().constData(), buffer.constData(), buffer.size(), MZ_DEFAULT_COMPRESSION)) {
        qWarning() << "Failed to add file" << filename << "to zip archive" << zipFilename;
        mz_zip_writer_end(&zip);
        return false;
    }

    // Clean up
    mz_zip_writer_finalize_archive(&zip);
    mz_zip_writer_end(&zip);
    qDebug() << "Zip complete";
    return true;
}

bool SimpleZipper::zipFolder(const QString& folder)
{
    QDir dir(folder);
    QString zipFilename = dir.dirName() + ".zip";
    dir.cdUp();
    zipFilename = dir.absolutePath() + "/" + zipFilename;
    return zipFolder(folder, zipFilename);
}

bool SimpleZipper::zipFolder(const QString& folder, const QString& zipFilename)
{
    qDebug() << "Zipping folder" << folder << "to" << zipFilename;

    // Get a list of all files in root level directory
    QDir dir(folder);
    QStringList files = dir.entryList(QDir::Files);

    // Create and open the output zip file
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));
    if (!mz_zip_writer_init_file(&zip, zipFilename.toUtf8().constData(), 0)) {
        qWarning() << "Failed to open output zip file" << zipFilename;
        return false;
    }

    // Add each file in the folder to the zip archive
    for (const auto& file : files) {
        QString filename = folder + "/" + file;
        QFile inFile(filename);
        qDebug() << "Writing" << filename;

        if (!inFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open file" << filename << "for reading";
            mz_zip_writer_end(&zip);
            return false;
        }

        QByteArray buffer = inFile.readAll();
        if (!mz_zip_writer_add_mem(&zip, file.toUtf8().constData(), buffer.constData(), buffer.size(), MZ_DEFAULT_COMPRESSION)) {
            qWarning() << "Failed to add file" << file << "to zip archive" << zipFilename;
            mz_zip_writer_end(&zip);
            return false;
        }
    }

    // Clean up
    mz_zip_writer_finalize_archive(&zip);
    mz_zip_writer_end(&zip);
    qDebug() << "Zip complete";
    return true;
}
