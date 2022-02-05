/* Author: Yang Meng
 * DataCommunicationI-ProgrammingAssignment-1 Client
 * Last edit at 10/17/2016
 */
import java.io.*;
import java.net.*;

public class Myclient {
	
	public static void main(String[] args) throws IOException{
		String filename = null, action = null, host = null;
		int port;
		
		//Verify the command input by users
		try{
			//Correct format of the command line: myclient Host Port_Number GET Filename
			if(args.length<4)
			{
				throw new IllegalArgumentException("Bad command\n");
			}
			//Obtain the host address
			host = args[0];
			//Obtain the port number
			port = Integer.parseInt(args[1]);
			//Obtain the action command
			action = args[2];
			//Obtain the file name
			filename = args[3];
			
			OutputStream Client_Login = System.out;
			//Begin to initialize the socket
			//Obtain a network socket connection to host and port
			Socket ClientSock = new Socket(host, port);
			//Obtain input stream of the socket
			InputStream Into_Client = ClientSock.getInputStream();
			//Obtain output stream of the socket
			PrintWriter Out_Client = new PrintWriter(new OutputStreamWriter(ClientSock.getOutputStream()));
			
			//Begin to execute GET command
			if(action.equals("GET"))
			{
				//Send HTTP command to the web server
				Out_Client.printf(action + " /" + filename + " HTTP/1.0\r\n");
				Out_Client.printf("Host: " + host + "\r\n\r\n");
				//Send it
				Out_Client.flush();				
				
				byte[] buffer = new byte[4896];
				int bytes_read;
												
				while((bytes_read = Into_Client.read(buffer)) != -1)
				{
					Client_Login.write(buffer, 0, bytes_read);
				}
				
				Client_Login.close();
			}
			else {
				if(action.equals("PUT"))
				{
					//Send file to Service
					InputStream From_File = null;
					File file = new File(filename);
					int ch;
					StringBuffer StringContent = new StringBuffer("");
					
					try{
						From_File = new FileInputStream(file);
						
						//Transfer it to char type
						while((ch = From_File.read()) != -1)
						{
							StringContent.append((char)ch);
						}
						
						From_File.close();
						System.out.println("File: " + StringContent + "has been successfully put");
						
						//Begin to upload file to the server
						Out_Client.println(action + " " + filename);
						Out_Client.println(StringContent + "\r\n");
						Out_Client.flush();
						
						From_File.close();
					}
					//If could not find file, throws the FileNotFoundException
					catch(FileNotFoundException e)
					{
						System.out.println("File " + file.getAbsolutePath() + "cannot be found.");
					}
					//Server throws IOException when server failed to read the file
					catch(IOException ioe)
					{
						System.out.println("Exceptino while reading the file" + ioe);
					}
				}
				else{
					System.out.println( action + "is an Invalid HTTP request");
					System.exit(1);
				}
			}
			//Close PrintWriter & Socket
			Out_Client.close();
			ClientSock.close();
			System.exit(0);
		}
		catch(UnknownHostException e){
			System.err.println("Cannot understand host: " + host);
			System.exit(1);
		}
		catch(IOException e){
			System.err.println("Cannot get IO from:" + host);
			System.exit(1);
		}
	}
}
