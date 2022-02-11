import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class ESPStop_Example {

	static long _LAST = 0;
	static boolean _READY = false;

	public static void main(String[] args) throws InterruptedException {

		new Thread() {
			public void run() {

				try (DatagramSocket socket = new DatagramSocket(3336)) {

					while (true) {

						DatagramPacket packet = new DatagramPacket(new byte[4], 4);
						socket.receive(packet);

						String msg = new String(packet.getData()).trim();
						_READY = msg.equals("OK");
						_LAST = System.currentTimeMillis();

					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}.start();

		while (true) {
			Thread.sleep(50);
			_READY = _READY && ((_LAST + 750) > System.currentTimeMillis());

			if (_READY) {
				System.out.println("Motion Enabled.");
			} else {
				System.out.println("DISABLED");
			}
		}
	}
}
