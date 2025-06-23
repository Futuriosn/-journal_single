import com.huatai.ficc.aurora.journal.Frame;
import com.huatai.ficc.aurora.journal.PageSize;
import com.huatai.ficc.aurora.journal.Reader;
import com.huatai.ficc.aurora.journal.proxy.JournalNative;

public class ReaderTest {
    public static void main(String[] args) {
        JournalNative.loadLibrary("journal_java_proxy");
        Reader rd = new Reader();
        rd.join("./tmp", "test1", 0, PageSize.Small);

        while (true) {
            if (rd.dataAvailable()) {
                Frame frame = rd.currentFrame();
                if (frame != null) {
                    byte[] data = frame.dataAsBytes();
                    System.out.println(new String(data));
                }
                rd.next();
            }
        }
    }
}
