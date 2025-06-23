import com.huatai.ficc.aurora.journal.PageSize;
import com.huatai.ficc.aurora.journal.Writer;
import com.huatai.ficc.aurora.journal.proxy.JournalNative;

import java.nio.charset.StandardCharsets;

import static java.lang.Thread.sleep;

public class WriterTest {
    public static void main(String[] args) {
        JournalNative.loadLibrary("journal_java_proxy");
        Writer wr = new Writer("./tmp", "test1", PageSize.Small);
        int i = 0;
        try {
            while (true) {
                String data;
                data = i + ", test++++++++++++++end";

                System.out.println(data);

                wr.writeBytesWithTime(System.nanoTime(), 100, data.getBytes(StandardCharsets.UTF_8));
                i++;
                Thread.sleep(1);
            }
        } catch (Exception e) {
            System.out.println("catch exception" + e);
        }
    }
}
