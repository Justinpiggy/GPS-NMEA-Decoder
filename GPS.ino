

int NMEA_Decode(char code[], int length);
boolean check_str(char str_a[], char str_b[], int a_start, int b_start, int str_length);

struct LL
{
  int dd;
  int mm_int;
  long mm_decimal;
  double mm_data;
  double data;
  char hs;
};

struct GPGGA
{
  int UTC_hh;
  int UTC_mm;
  int UTC_ss;
  int UTC_ms;
  LL Latitude;
  LL Longitude;
  int GPS_status;
  int GPS_count;
  double HDOP;
  double Elevation;
  double Geo_Elevation;
  int DEF_ss;
  int DEF_id;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};


struct GPGSA
{
  char SAT_mode;
  int SAT_count;
  int SAT_id[12];
  double PDOP;
  double HDOP;
  double VDOP;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPGSV
{
  int GSV_count;
  int GSV_id;
  int SAT_count[4];
  int SAT_id[4];
  int SAT_elevation[4];
  int SAT_azimuth[4];
  int SAT_SNR[4];
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPRMC
{
  int UTC_hh;
  int UTC_mm;
  int UTC_ss;
  int UTC_ms;
  char GPS_status;
  LL Latitude;
  LL Longitude;
  double GND_speed;
  double GND_heading;
  int UTC_D_dd;
  int UTC_D_mm;
  int UTC_D_yy;
  double MEG_deg;
  char MEG_dir;
  char GPS_mode;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPVTG
{
  char GPS_status;
  double NRH_real;
  char NRH_meg;
  double GND_speed_knot;
  double GND_speed_kmh;
  char GPS_mode;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPGLL
{
  LL Latitude;
  LL Longitude;
  int UTC_hh;
  int UTC_mm;
  int UTC_ss;
  char GPS_status;
  char GPS_mode;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPZDA
{
  int UTC_hh;
  int UTC_mm;
  int UTC_ss;
  int UTC_D_dd;
  int UTC_D_mm;
  int UTC_D_yy;
  int LOC_hh;
  int LOC_mm;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPSData
{
  GPGGA GGA;
  GPGSA GSA;
  GPGSV GSV[3];
  int GSV_count;
  GPRMC RMC;
  GPVTG VTG;
  GPGLL GLL;
  GPZDA ZDA;
};

GPSData now;

char Serial_code[200];
int Serial_length;
void setup() {
  SerialUSB.begin(115200);
  while (!SerialUSB)
  {
  }
  SerialUSB.println("GPS Start");
  // put your setup code here, to run once:
}





void loop() {
  // put your main code here, to run repeatedly:
  if (SerialUSB.available() > 0)
  {
    SerialUSB.println("Response:");
    while (SerialUSB.available() > 0) {
      Serial_length = SerialUSB.readBytesUntil('\r', (char*)Serial_code, 200);
    }
    SerialUSB.println(Serial_length);
    SerialUSB.println("Decoding");
    NMEA_Decode(Serial_code, Serial_length);
    SerialUSB.println("GGA Data:");
    SerialUSB.println(now.GGA.UTC_hh);
    SerialUSB.println(now.GGA.UTC_mm);
    SerialUSB.println(now.GGA.UTC_ss);
    SerialUSB.println(now.GGA.UTC_ms);
    SerialUSB.println(now.GGA.Latitude.dd);
    SerialUSB.println(now.GGA.Latitude.mm_int);
    SerialUSB.println(now.GGA.Latitude.mm_decimal);
    SerialUSB.println(now.GGA.Latitude.mm_data);
    SerialUSB.println(now.GGA.Latitude.hs);
    SerialUSB.println(now.GGA.Longitude.dd);
    SerialUSB.println(now.GGA.Longitude.mm_int);
    SerialUSB.println(now.GGA.Longitude.mm_decimal);
    SerialUSB.println(now.GGA.Longitude.mm_data);
    SerialUSB.println(now.GGA.Longitude.hs);
    SerialUSB.println(now.GGA.GPS_status);
    SerialUSB.println(now.GGA.GPS_count);
    SerialUSB.println(now.GGA.HDOP);
    SerialUSB.println(now.GGA.Elevation);
    SerialUSB.println(now.GGA.Geo_Elevation);
    SerialUSB.println(now.GGA.DEF_ss);
    SerialUSB.println(now.GGA.DEF_id);
    SerialUSB.println(now.GGA.Rcv_Checksum);
    SerialUSB.println(now.GGA.Cal_Checksum);


    SerialUSB.println("GSA Data:");
    SerialUSB.println(now.GSA.SAT_mode);
    SerialUSB.println(now.GSA.SAT_count);
    for (int i = 0; i < 12; i++)
    {
      SerialUSB.print(now.GSA.SAT_id[i]);
      SerialUSB.print(",");
    }
    SerialUSB.println();
    SerialUSB.println(now.GSA.PDOP);
    SerialUSB.println(now.GSA.HDOP);
    SerialUSB.println(now.GSA.VDOP);
    SerialUSB.println(now.GSA.Rcv_Checksum);
    SerialUSB.println(now.GSA.Cal_Checksum);

    SerialUSB.println("Done");
  }
}




int NMEA_Decode(char code[], int code_length)
{
  long time = micros();
  char temp[100];
  int ptemp;
  char t[10];
  int i = 0;
  if (check_str(code, "GPGGA", 0, 0, 5))
  {
    i = 6;

    now.GGA.UTC_hh = (code[i] - '0') * 10 + (code[i + 1] - '0');
    now.GGA.UTC_mm = (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    now.GGA.UTC_ss = (code[i + 4] - '0') * 10 + (code[i + 5] - '0');
    now.GGA.UTC_ms = (code[i + 7] - '0') * 10 + (code[i + 8] - '0');
    i = i + 10;

    now.GGA.Latitude.dd = (code[i] - '0') * 10 + (code[i + 1] - '0');
    now.GGA.Latitude.mm_int = (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    now.GGA.Latitude.mm_decimal = (code[i + 5] - '0') * 10000 + (code[i + 6] - '0') * 1000 + (code[i + 7] - '0') * 100 + (code[i + 8] - '0') * 10 + (code[i + 9] - '0');
    now.GGA.Latitude.mm_data = now.GGA.Latitude.mm_decimal;
    now.GGA.Latitude.mm_data /= 100000;
    now.GGA.Latitude.mm_data += now.GGA.Latitude.mm_int;
    now.GGA.Latitude.data = now.GGA.Latitude.dd + now.GGA.Latitude.mm_data / 60;
    now.GGA.Latitude.hs = code[i + 11];
    i = i + 13;

    now.GGA.Longitude.dd = (code[i] - '0') * 100 + (code[i + 1] - '0') * 10 + (code[i + 2] - '0');
    now.GGA.Longitude.mm_int = (code[i + 3] - '0') * 10 + (code[i + 4] - '0');
    now.GGA.Longitude.mm_decimal = (code[i + 6] - '0') * 10000 + (code[i + 7] - '0') * 1000 + (code[i + 8] - '0') * 100 + (code[i + 9] - '0') * 10 + (code[i + 10] - '0');
    now.GGA.Longitude.mm_data = now.GGA.Longitude.mm_decimal;
    now.GGA.Longitude.mm_data /= 100000;
    now.GGA.Longitude.mm_data += now.GGA.Longitude.mm_int;
    now.GGA.Longitude.data = now.GGA.Longitude.dd + now.GGA.Longitude.mm_data / 60;
    now.GGA.Longitude.hs = code[i + 12];
    i = i + 14;

    now.GGA.GPS_status = code[i] - '0';
    i = i + 2;

    now.GGA.GPS_count = (code[i] - '0') * 10 + (code[i + 1] - '0');
    i = i + 3;

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i++;
    temp[ptemp] = 0;
    now.GGA.HDOP = atof(temp);

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i = i + 3;
    temp[ptemp] = 0;
    now.GGA.Elevation = atof(temp);

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i = i + 3;
    temp[ptemp] = 0;
    now.GGA.Geo_Elevation = atof(temp);

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i++;
    temp[ptemp] = 0;
    now.GGA.DEF_ss = atoi(temp);
    ptemp = 0;
    while (code[i] != '*')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i++;
    temp[ptemp] = 0;
    now.GGA.DEF_id = atoi(temp);

    now.GGA.Rcv_Checksum = (((code[i] >= 'A') && (code[i] <= 'F')) ? (code[i] - 'A' + 10) : (code[i] - '0')) * 16 + (((code[i + 1] >= 'A') && (code[i + 1] <= 'F')) ? (code[i + 1] - 'A' + 10) : (code[i + 1] - '0'));
    now.GGA.Cal_Checksum = 0;
    for (int counter = 0; counter < i - 1; counter++)
    {
      now.GGA.Cal_Checksum ^= code[counter];
    }
  }


  if (check_str(code, "GPGSA", 0, 0, 5))
  {
    i = 6;
    now.GSA.SAT_mode = code[i];
    i = i + 2;

    now.GSA.SAT_count = code[i] - '0';
    i = i + 2;
    int comma = 0;
    do {
      if (code[i] != ',')
      {
        now.GSA.SAT_id[comma] = (code[i] - '0') * 10 + (code[i + 1] - '0');
        i = i + 2;
      }
      i++;
      comma++;
    }
    while (comma < 12);

    SerialUSB.println(i);
    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i++;
    temp[ptemp] = 0;
    now.GSA.PDOP = atof(temp);

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i = i++;
    temp[ptemp] = 0;
    now.GSA.HDOP = atof(temp);

    ptemp = 0;
    while (code[i] != '*')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i++;
    temp[ptemp] = 0;
    now.GSA.VDOP = atof(temp);

    now.GSA.Rcv_Checksum = (((code[i] >= 'A') && (code[i] <= 'F')) ? (code[i] - 'A' + 10) : (code[i] - '0')) * 16 + (((code[i + 1] >= 'A') && (code[i + 1] <= 'F')) ? (code[i + 1] - 'A' + 10) : (code[i + 1] - '0'));
    now.GSA.Cal_Checksum = 0;
    for (int counter = 0; counter < i - 1; counter++)
    {
      now.GSA.Cal_Checksum ^= code[counter];
    }
  }

  SerialUSB.println(micros() - time);
  return 0;
}

boolean check_str(char str_a[], char str_b[], int a_start, int b_start, int str_length)
{
  for (int i = a_start, j = b_start; i < a_start + str_length; i++, j++)
  {
    if (str_a[i] != str_b[j])
    {
      return false;
    }
  }
  return true;
}



