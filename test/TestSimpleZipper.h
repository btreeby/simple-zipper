#ifndef TESTSIMPLEZIPPER_H
#define TESTSIMPLEZIPPER_H

#include <QtCore>
#include <QtTest/QtTest>

#include "SimpleZipper.h"

/**
 * @class   TestSimpleZipper
 *
 * @brief   Unit tests for SimpleZipper class.
 *
 * @details The TestSimpleZipper class implements unit tests for the static methods in the SimpleZipper class.
 *          It creates three text files, and zips and unzips these by file and folder, and checks the file
 *          contents survive the zip-unzip.
 */
class TestSimpleZipper : public QObject {
    Q_OBJECT

private:
    QDir mTempDir;
    QFile mFile1;
    QFile mFile2;
    QFile mFile3;

private slots:
    /**
     * @brief Creates a temporary directory with three text files.
     */
    void initTestCase() {
        // Create a temporary directory
        mTempDir = QDir(QDir::tempPath() + "/TestSimpleZipper");
        QVERIFY(mTempDir.mkpath("."));

        // Create three text files
        mFile1.setFileName(mTempDir.filePath("mFile1.txt"));
        QVERIFY(mFile1.open(QIODevice::WriteOnly));
        mFile1.write("Hello World!");
        mFile1.close();

        mFile2.setFileName(mTempDir.filePath("mFile2.txt"));
        QVERIFY(mFile2.open(QIODevice::WriteOnly));
        mFile2.write("Goodbye World!");
        mFile2.close();

        mFile3.setFileName(mTempDir.filePath("mFile3.txt"));
        QVERIFY(mFile3.open(QIODevice::WriteOnly));
        mFile3.write("Lorem Ipsum.");
        mFile3.close();
    }

    /**
     * @brief Zips and unzips the temporary directory and checks the files are the same.
     */
    void testZipDirectory()
    {
        // Name for zip file
        QString zipPath = mTempDir.filePath("testZipper.zip");

        // Zip the temporary directory
        QVERIFY(SimpleZipper::zipFolder(mTempDir.absolutePath(), zipPath));

        // Check the file exists
        QVERIFY(QFile::exists(zipPath));

        // Directory for unzipping
        QString tempUnzipDir = mTempDir.filePath("testZipperUnzip");

        // Unzip the zip file to the temporary directory
        QVERIFY(SimpleZipper::unzipFile(zipPath, tempUnzipDir));

        // Check the contents of the unzipped files are the same as the original files
        QFile unzippedFile1(tempUnzipDir + "/mFile1.txt");
        QFile unzippedFile2(tempUnzipDir + "/mFile2.txt");
        QFile unzippedFile3(tempUnzipDir + "/mFile3.txt");

        QVERIFY(unzippedFile1.open(QIODevice::ReadOnly));
        QVERIFY(unzippedFile2.open(QIODevice::ReadOnly));
        QVERIFY(unzippedFile3.open(QIODevice::ReadOnly));

        QVERIFY(mFile1.open(QIODevice::ReadOnly));
        QVERIFY(mFile2.open(QIODevice::ReadOnly));
        QVERIFY(mFile3.open(QIODevice::ReadOnly));

        QCOMPARE(unzippedFile1.readAll(), mFile1.readAll());
        QCOMPARE(unzippedFile2.readAll(), mFile2.readAll());
        QCOMPARE(unzippedFile3.readAll(), mFile3.readAll());

        // Close original files
        mFile1.close();
        mFile2.close();
        mFile3.close();
    }

    /**
     * @brief Zips and unzips a single text file and check the output is the same.
     */
    void testZipFiles()
    {
        QFileInfo fileInfo(mFile1.fileName());
        QString zipFileName = fileInfo.absoluteDir().path() + "/" + fileInfo.baseName() + ".zip";
        QString unzipFileName = fileInfo.absoluteDir().path() + "/" + fileInfo.baseName() + "/" + fileInfo.fileName();

        // Zip the file
        QVERIFY(SimpleZipper::zipFile(mFile1.fileName()));

        // Check the file exists
        QVERIFY(QFile::exists(zipFileName));

        // Unzip the file
        QVERIFY(SimpleZipper::unzipFile(zipFileName, fileInfo.absoluteDir().path() + "/" + fileInfo.baseName()));

        // Check the unzipped file exists
        QVERIFY(QFile::exists(unzipFileName));

        // Compare the unzipped file to the original file
        QFile unzippedFile(unzipFileName);
        QVERIFY(unzippedFile.open(QIODevice::ReadOnly));
        QVERIFY(mFile1.open(QIODevice::ReadOnly));
        QCOMPARE(unzippedFile.readAll(), mFile1.readAll());

        // Close original file
        mFile1.close();
    }

    /**
     * @brief Deletes the temporary directory and all files created in it.
     */
    void cleanupTestCase() {
        QVERIFY(mTempDir.removeRecursively());
    }

};

QTEST_MAIN(TestSimpleZipper)

#endif // TESTSIMPLEZIPPER_H
