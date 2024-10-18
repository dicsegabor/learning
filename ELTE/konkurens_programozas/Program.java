public class Program {
  public static void main(String[] args) throws InterruptedException {

    Thread t1 = new Thread(() -> {
      for (int i = 0; i < 1000; i++) {
        System.out.print(i + " ");
        try {
          Thread.sleep(5);
        } catch (InterruptedException e) {
          System.out.println("Thread was interrupted!");
        }
      }
    });

    Thread t2 = new Thread(() -> {
      for (int i = 0; i < 1000; i++) {
        System.out.print(-i + " ");
      }
      try {
        Thread.sleep(5);
      } catch (InterruptedException e) {
        System.out.println("Thread was interrupted!");
      }
    });

    t1.start();
    t2.start();

    Thread.sleep(1000);
    t1.interrupt();
    t2.interrupt();

    t1.join();
    t2.join();

    System.out.println("Kész");
  }

  public static void fakePrintln(String string) {
    for (int i = 0; i < string.length(); i++) {
      System.out.print(string.charAt(i));
    }
    System.out.println();
  }
}
