import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ConfigCheckerRunner {

    public static void main(String[] args) {
        try {
            ProcessBuilder builder = new ProcessBuilder(
                "..\\checker.exe",
                "..\\sample\\config.txt",
                "..\\sample\\contract.txt"
            );


            builder.redirectErrorStream(true);
            Process process = builder.start();

            // Read output (JSON)
            BufferedReader reader = new BufferedReader(
                new InputStreamReader(process.getInputStream())
            );

            String line;
            System.out.println("C++ Engine Output:");
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

            int exitCode = process.waitFor();
            System.out.println("\nProcess exited with code: " + exitCode);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
