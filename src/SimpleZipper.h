#ifndef SIMPLEZIPPER_HPP
#define SIMPLEZIPPER_HPP

#include <QString>
#include "miniz.h"

/**
 * @class   SimpleZipper
 *
 * @brief   A class to provide simple zipping and unzipping functionality based on miniz and Qt.
 *
 * @details This class implements a very simple wrapper around the miniz high performance data compression library.
 *          Three static functions are provided to zip a file or folder, and to unzip a file. Basic debug information
 *          is displayed.
 */
class SimpleZipper {
public:
    /**
     * @brief   Unzip a zip file using miniz and Qt.
     *
     * @details This function takes a zip file name and extracts the contents of the zip file
     *          using the miniz library and the Qt file abstraction classes. The uncompressed
     *          file/s are saved into a folder with the same name as the input file.
     *
     * @param   zipFilename The name of the zip file to extract.
     *
     * @return  True if the zip file was extracted successfully, false otherwise.
     */
    static bool unzipFile(const QString& zipFilename);

    /**
     * @brief   Unzip a zip file using miniz and Qt.
     *
     * @details This function takes a zip file name and an output folder as input and extracts the contents of the zip file
     *          using the miniz library and the Qt file abstraction classes.
     *
     * @param   zipFilename The name of the zip file to extract.
     * @param   outFolder The name of the folder to extract the contents of the zip file to.
     *
     * @return  True if the zip file was extracted successfully, false otherwise.
     */
    static bool unzipFile(const QString& zipFilename, const QString& folder);

    /**
     * @brief   Zip a single file using miniz and Qt.
     *
     * @details This function takes a file name as input and compresses it using the miniz library and the Qt file
     *          abstraction classes. The compressed file is saved in the same directory as the input file with a .zip
     *          extension. The default compression level is used.
     *
     * @param   fileName The name of the file to compress.
     *
     * @return  True if the file was compressed successfully, false otherwise.
     */
    static bool zipFile(const QString& filename);

    /**
     * @brief   Zip a single file using miniz and Qt.
     *
     * @details This function takes a file name and a zip file name as inputs and compresses it using the
     *          miniz library and the Qt file abstraction classes. The default compression level is used.
     *
     * @param   fileName The name of the file to compress.
     * @param   zipFilename The name of the generated zip file.
     *
     * @return  True if the file was compressed successfully, false otherwise.
     */
    static bool zipFile(const QString& filename, const QString& zipFilename);

    /**
     * @brief   Zip a folder and all its contents recursively using miniz and Qt.
     *
     * @details This function takes a folder name as input and compresses all the files in the folder and
     *          its subfolders into a zip file using the miniz library and the Qt file abstraction classes
     *          while preserving the directory structure. The default compression level is used.
     *          The compressed file is saved in the same directory as the input folder with a .zip
     *          extension.
     *
     * @param   folder The name of the folder to compress.
     *
     * @return  True if the folder was compressed successfully, false otherwise.
     */
    static bool zipFolder(const QString& folder);

    /**
     * @brief   Zip a folder and all its contents recursively using miniz and Qt.
     *
     * @details This function takes a folder name and a zip file name as inputs and compresses all the files
     *          in the folder and its subfolders into a zip file using the miniz library and the Qt file
     *          abstraction classes while preserving the directory structure. The default compression level
     *          is used.
     *
     * @param   folder The name of the folder to compress.
     * @param   zipFilename The name of the zip file to create.
     *
     * @return  True if the folder was compressed successfully, false otherwise.
     */
    static bool zipFolder(const QString& folder, const QString& zipFilename);

private:
    /**
     * @brief   Recursively add all files in a folder and its subfolders to a zip archive with the appropriate prefix.
     *
     * @details This function is used by zipFolder to traverse the directory tree and add all files and
     *          subfolders to the zip archive with the appropriate directory structure.
     *
     * @param   zip A pointer to the miniz zip archive object to add files to.
     * @param   folder The name of the folder to add files from.
     * @param   prefix The prefix to add to the file names in the zip archive to preserve the directory structure.
     *
     * @return  True if all files were added successfully, false otherwise.
     */
    static bool addFolderToZip(mz_zip_archive* zip, const QString& folder, const QString& prefix);
};

#endif // SIMPLEZIPPER_HPP
