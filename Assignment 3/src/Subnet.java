import java.util.Scanner;

public class Subnet {
    Scanner sc  = new Scanner(System.in);

    public void subnetmask(){
        String networkadd;
        String numb;
        System.out.println("Enter Network address: ");
        networkadd = sc.next();
        numb = networkadd.split("\\.")[0];
        String cla = "";
        int num1 = Integer.parseInt(numb);
        String mask = " ";
        if(num1<=127)
        {
            mask = "255.0.0.0";
            System.out.println("Class A");
            cla = "A";
            System.out.println("Default Subnet mask: " + mask);
        }else if(num1>=128 && num1<=191)
        {
            mask = "255.255.0.0";
            System.out.println("Class B");
            cla = "B";
            System.out.println("Default Subnet mask: " + mask);
        }else if(num1>=192 && num1<=223)
        {
            mask = "255.255.255.0";
            System.out.println("Class C");
            cla = "C";
            System.out.println("Default Subnet mask: " + mask);
        }
        int subnetworks;
        System.out.println("Enter number of subnetworks to form: ");
        subnetworks = sc.nextInt();
        int bits=(int)Math.ceil(Math.log(subnetworks)/Math.log(2));
        System.out.println("No. of bits: "+bits);

        int addr = 0;
        for(int i=7;i > 7-bits;i--)
        {
            addr=addr+(int)Math.pow(2, i);
        }
//        System.out.println(addr);
        if(cla == "A")
        {
            System.out.println("Subnet mask: 255."+ addr + ".0.0");
        }else if(cla == "B")
        {
            System.out.println("Subnet mask: 255.255."+ addr + ".0");
        }else if(cla == "C")
        {
            System.out.println("Subnet mask: 255.255.255."+ addr );
        }
        int actualsubnetworks = (int)Math.pow(2, bits);
        int hps = 256/actualsubnetworks;
        System.out.println("No. of host per subnet: "+ hps);
        String binaryOctet2;

//        int index = 0;
//        for (String string : octets){
//            int octet = Integer.parseInt(string);
//            eoctet[index] = Integer.toBinaryString(octet);
//
//            System.out.println(eoctet[index]);
//            index++;
//        }
//        for(int i = 0;i<4;i++){
//            eoctet[i] = Integer.toBinaryString(Integer.parseInt(octets[i]));
//            System.out.println(eoctet[i]);
//        }
        int hps1 = hps-1;
        int count = 0;

        for(int i =0;i<actualsubnetworks;i++)
        {
            System.out.println("Subnet "+ i+ " range: ");
            System.out.println( count + " to "+ (count+hps1));
            count = count+hps1+1;
        }
        int ch = 1;
        while(ch==1)
        {
            String ip;
            System.out.println("Enter IP adrress: ");
            ip = sc.next();
            String octets[] = ip.split("\\.");
//            String eoctet[] = new String[4];
            int subnetgroup = 0;
            if(cla == "A")
            {
                subnetgroup = Integer.parseInt(octets[1])/hps;
            }else if(cla == "B"){
                subnetgroup = Integer.parseInt(octets[2])/hps;
            }else if(cla == "C"){
                subnetgroup = Integer.parseInt(octets[3])/hps;
             }

            System.out.println("It belongs to subnet: "+subnetgroup);
            System.out.println("Do you want to continue? ");
            ch = sc.nextInt();
        }




    }



    public static void main(String args[]){
        int n;
        Scanner sc  = new Scanner(System.in);
        Subnet s = new Subnet();
        do {
            System.out.println("1.Calculate subnets\n0.Exit");
            n = sc.nextInt();
            switch (n){
                case 1:s.subnetmask();break;
            }
        }while(n!=0);

    }

}
