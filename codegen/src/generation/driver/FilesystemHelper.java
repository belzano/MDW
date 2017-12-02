package generation.driver;

import com.google.common.base.Strings;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.zip.CRC32;
import java.util.zip.Checksum;

public class FilesystemHelper {

    public static boolean mkdir(String directory) {
        return mkdir(new File(directory));
    }

    public static boolean mkdir(File directory) {
        try {
            Files.createDirectories(Paths.get(directory.toURI()));
            return true;
        } catch (IOException ex) {
            System.err.println("Failed to create output dir " + ex.getMessage());
        }
        return false;
    }

    public static boolean setFile(String absPath, String fileName, String newContentStr) {
        try {
            byte[] newContent = newContentStr.getBytes("UTF-8");
            mkdir(absPath);
            File outputFile = Paths.get(absPath, fileName).toFile();
            if (outputFile.exists()) {
                FileInputStream inputStream = new FileInputStream(outputFile);
                byte[] currContent = new byte[(int)outputFile.length()];
                inputStream.read(currContent);
                long curChecksumValue = checksum(currContent);
                long newChecksumValue = checksum(newContent);
                if (curChecksumValue == newChecksumValue) {
                    System.out.println("[" + fileName + "] skipping write (checksum match)");
                    return true;
                }
            }
            FileOutputStream outputStream = new FileOutputStream(outputFile);
            outputStream.write(newContent);
            System.out.println("[" + fileName + "] written");
            outputStream.close();
            return true;
        } catch (Exception ex) {
            System.err.println("Failed to create file " + ex.getMessage());
        }

        return false;
    }

    public static long checksum(byte[] bytes) {
        Checksum checksum = new CRC32();
        checksum.update(bytes, 0, bytes.length);
        return checksum.getValue();
    }
}
