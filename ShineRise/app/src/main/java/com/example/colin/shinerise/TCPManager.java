package com.example.colin.shinerise;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class TCPManager {
    public static String GetDate(String uri, String message) throws IOException {
        Socket socket = null;
        BufferedReader reader = null;
        StringBuilder sb = new StringBuilder();
        String line;

        try {
            socket = new Socket(uri, 3490);
            message = "1" + message;
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            out.println(message);
            reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            socket.close();


            while ((line = reader.readLine()) != null) {
                sb.append(line + "\n");
            }
            return sb.toString();
        } catch (Exception e) {
            e.printStackTrace();
            return null;
         } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e) {
                    e.printStackTrace();
                    return null;
                }
            }
        }
    }
}
