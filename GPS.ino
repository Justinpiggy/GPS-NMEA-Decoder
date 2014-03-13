
int ShowData(int code_type);
int NMEA_Decode(char code[], int length);
boolean check_str(char str_a[], char str_b[], int a_start, int b_start, int str_length);

struct LL
{
  byte dd;
  byte mm_int;
  long mm_decimal;
  double mm_data;
  double data;
  char hs;
};

struct GPGGA
{
  byte UTC_hh;
  byte UTC_mm;
  byte UTC_ss;
  byte UTC_ms;
  LL Latitude;
  LL Longitude;
  byte GPS_status;
  byte GPS_count;
  double HDOP;
  double Elevation;
  double Geo_Elevation;
  byte DEF_ss;
  int DEF_id;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};


struct GPGSA
{
  char SAT_mode;
  byte SAT_count;
  byte SAT_id[12];
  double PDOP;
  double HDOP;
  double VDOP;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPGSV
{
  byte GSV_count;
  byte GSV_id;
  byte SAT_count;
  byte SAT_id[4];
  byte SAT_elevation[4];
  int SAT_azimuth[4];
  byte SAT_SNR[4];
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPRMC
{
  byte UTC_hh;
  byte UTC_mm;
  byte UTC_ss;
  byte UTC_ms;
  char GPS_status;
  LL Latitude;
  LL Longitude;
  double GND_speed;
  double GND_heading;
  byte UTC_D_dd;
  byte UTC_D_mm;
  byte UTC_D_yy;
  double MEG_deg;
  char MEG_dir;
  char GPS_mode;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPVTG
{
  int NRH_real;
  int NRH_meg;
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
  int UTC_ms;
  char GPS_status;
  char GPS_mode;
  unsigned int Rcv_Checksum;
  unsigned int Cal_Checksum;
};

struct GPZDA
{
  byte UTC_hh;
  byte UTC_mm;
  byte UTC_ss;
  byte UTC_ms;
  byte UTC_D_dd;
  byte UTC_D_mm;
  int UTC_D_yy;
  byte LOC_hh;
  byte LOC_mm;
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
}





void loop() {
  if (SerialUSB.available() > 0)
  {
    SerialUSB.println("Response:");
    while (SerialUSB.available() > 0) {
      Serial_length = SerialUSB.readBytesUntil('\r', (char*)Serial_code, 200);
    }
    SerialUSB.println(Serial_length);
    SerialUSB.println("Decoding");
    long time = micros();
    int code_type = NMEA_Decode(Serial_code, Serial_length);
    SerialUSB.println(micros() - time);
    
    ShowData(code_type);

    SerialUSB.println("Done");
  }
}


int ShowData(int code_type)
{
  switch (code_type)
    {
      case 1:
        {
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
        }
        break;
      case 2:
        {
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
        }
        break;


      case 3:
        {
          SerialUSB.println("GSV Data:");
          SerialUSB.println(now.GSV_count);
          for (int i = 0; i < 3; i++)
          {
            SerialUSB.print("GSV Data set ");
            SerialUSB.println(i);
            SerialUSB.println(now.GSV[i].GSV_count);
            SerialUSB.println(now.GSV[i].GSV_id);
            SerialUSB.println(now.GSV[i].SAT_count);
            for (int j = 0; j < 4; j++)
            {
              SerialUSB.println(now.GSV[i].SAT_id[j]);
              SerialUSB.println(now.GSV[i].SAT_elevation[j]);
              SerialUSB.println(now.GSV[i].SAT_azimuth[j]);
              SerialUSB.println(now.GSV[i].SAT_SNR[j]);
            }
            SerialUSB.println(now.GSV[i].Rcv_Checksum);
            SerialUSB.println(now.GSV[i].Cal_Checksum);

          }

        }
        break;


      case 4:
        {
          SerialUSB.println("RMC Data:");
          SerialUSB.println(now.RMC.UTC_hh);
          SerialUSB.println(now.RMC.UTC_mm);
          SerialUSB.println(now.RMC.UTC_ss);
          SerialUSB.println(now.RMC.UTC_ms);
          SerialUSB.println(now.RMC.Latitude.dd);
          SerialUSB.println(now.RMC.Latitude.mm_int);
          SerialUSB.println(now.RMC.Latitude.mm_decimal);
          SerialUSB.println(now.RMC.Latitude.mm_data);
          SerialUSB.println(now.RMC.Latitude.hs);
          SerialUSB.println(now.RMC.Longitude.dd);
          SerialUSB.println(now.RMC.Longitude.mm_int);
          SerialUSB.println(now.RMC.Longitude.mm_decimal);
          SerialUSB.println(now.RMC.Longitude.mm_data);
          SerialUSB.println(now.RMC.Longitude.hs);
          SerialUSB.println(now.RMC.GND_speed);
          SerialUSB.println(now.RMC.GND_heading);
          SerialUSB.println(now.RMC.UTC_D_dd);
          SerialUSB.println(now.RMC.UTC_D_mm);
          SerialUSB.println(now.RMC.UTC_D_yy);
          SerialUSB.println(now.RMC.MEG_deg);
          SerialUSB.println(now.RMC.MEG_dir);
          SerialUSB.println(now.RMC.GPS_mode);
          SerialUSB.println(now.RMC.Rcv_Checksum);
          SerialUSB.println(now.RMC.Cal_Checksum);
        }
        break;

      case 5:
        {
          SerialUSB.println("VTG Data:");
          SerialUSB.println(now.VTG.NRH_real);
          SerialUSB.println(now.VTG.NRH_meg);
          SerialUSB.println(now.VTG.GND_speed_knot);
          SerialUSB.println(now.VTG.GND_speed_kmh);
          SerialUSB.println(now.VTG.GPS_mode);
          SerialUSB.println(now.VTG.Rcv_Checksum);
          SerialUSB.println(now.VTG.Cal_Checksum);
        }
        break;

      case 6:
        {
          SerialUSB.println("GLL Data:");

          SerialUSB.println(now.GLL.Latitude.dd);
          SerialUSB.println(now.GLL.Latitude.mm_int);
          SerialUSB.println(now.GLL.Latitude.mm_decimal);
          SerialUSB.println(now.GLL.Latitude.mm_data);
          SerialUSB.println(now.GLL.Latitude.hs);
          SerialUSB.println(now.GLL.Longitude.dd);
          SerialUSB.println(now.GLL.Longitude.mm_int);
          SerialUSB.println(now.GLL.Longitude.mm_decimal);
          SerialUSB.println(now.GLL.Longitude.mm_data);
          SerialUSB.println(now.GLL.Longitude.hs);
          SerialUSB.println(now.GLL.UTC_hh);
          SerialUSB.println(now.GLL.UTC_mm);
          SerialUSB.println(now.GLL.UTC_ss);
          SerialUSB.println(now.GLL.UTC_ms);
          SerialUSB.println(now.GLL.GPS_status);
          SerialUSB.println(now.GLL.GPS_mode);
          SerialUSB.println(now.GLL.Rcv_Checksum);
          SerialUSB.println(now.GLL.Cal_Checksum);
        }
        break;

      case 7:
        {
          SerialUSB.println("ZDA Data:");
          SerialUSB.println(now.ZDA.UTC_hh);
          SerialUSB.println(now.ZDA.UTC_mm);
          SerialUSB.println(now.ZDA.UTC_ss);
          SerialUSB.println(now.ZDA.UTC_ms);
          SerialUSB.println(now.ZDA.UTC_D_dd);
          SerialUSB.println(now.ZDA.UTC_D_mm);
          SerialUSB.println(now.ZDA.UTC_D_yy);
          SerialUSB.println(now.ZDA.LOC_hh);
          SerialUSB.println(now.ZDA.LOC_mm);
          SerialUSB.println(now.ZDA.Rcv_Checksum);
          SerialUSB.println(now.ZDA.Cal_Checksum);
        }
        break;
    }
    return 0;
}



int NMEA_Decode(char code[], int code_length)
{
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
    return 1;
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
    return 2;
  }

  if (check_str(code, "GPGSV", 0, 0, 5))
  {
    i = 6;

    now.GSV_count = code[i] - '0';
    i = i + 2;

    int GSV_id = code[i] - '0' - 1;
    now.GSV[GSV_id].GSV_count = now.GSV_count;
    now.GSV[GSV_id].GSV_id = GSV_id + 1;
    i = i + 2;

    now.GSV[GSV_id].SAT_count = (code[i] - '0') * 10 + (code[i + 1] - '0');
    i = i + 3;

    int sat_counter = 0;
    do {
      if (code[i] != ',')
      {
        now.GSV[GSV_id].SAT_id[sat_counter] = (code[i] - '0') * 10 + (code[i + 1] - '0');
        i = i + 2;
      }
      i++;
      if (code[i] != ',')
      {
        now.GSV[GSV_id].SAT_elevation[sat_counter] = (code[i] - '0') * 10 + (code[i + 1] - '0');
        i = i + 2;
      }
      i++;
      if (code[i] != ',')
      {
        now.GSV[GSV_id].SAT_azimuth[sat_counter] = (code[i] - '0') * 100 + (code[i + 1] - '0') * 10 + (code[i + 2] - '0');
        i = i + 3;
      }
      i++;
      if ((code[i] != ',') && (code[i] != '*'))
      {
        now.GSV[GSV_id].SAT_SNR[sat_counter] = (code[i] - '0') * 10 + (code[i + 1] - '0');
        i = i + 2;
      }
      i++;
      sat_counter++;
    }
    while (sat_counter < 4);
    now.GSV[GSV_id].Rcv_Checksum = (((code[i] >= 'A') && (code[i] <= 'F')) ? (code[i] - 'A' + 10) : (code[i] - '0')) * 16 + (((code[i + 1] >= 'A') && (code[i + 1] <= 'F')) ? (code[i + 1] - 'A' + 10) : (code[i + 1] - '0'));
    now.GSV[GSV_id].Cal_Checksum = 0;
    for (int counter = 0; counter < i - 1; counter++)
    {
      now.GSV[GSV_id].Cal_Checksum ^= code[counter];
    }
    return 3;
  }

  if (check_str(code, "GPRMC", 0, 0, 5))
  {
    i = 6;

    now.RMC.UTC_hh = (code[i] - '0') * 10 + (code[i + 1] - '0');
    now.RMC.UTC_mm = (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    now.RMC.UTC_ss = (code[i + 4] - '0') * 10 + (code[i + 5] - '0');
    now.RMC.UTC_ms = (code[i + 7] - '0') * 10 + (code[i + 8] - '0');
    i = i + 10;

    now.RMC.GPS_status = code[i];
    i = i + 2;

    now.RMC.Latitude.dd = (code[i] - '0') * 10 + (code[i + 1] - '0');
    now.RMC.Latitude.mm_int = (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    now.RMC.Latitude.mm_decimal = (code[i + 5] - '0') * 10000 + (code[i + 6] - '0') * 1000 + (code[i + 7] - '0') * 100 + (code[i + 8] - '0') * 10 + (code[i + 9] - '0');
    now.RMC.Latitude.mm_data = now.RMC.Latitude.mm_decimal;
    now.RMC.Latitude.mm_data /= 100000;
    now.RMC.Latitude.mm_data += now.RMC.Latitude.mm_int;
    now.RMC.Latitude.data = now.RMC.Latitude.dd + now.RMC.Latitude.mm_data / 60;
    now.RMC.Latitude.hs = code[i + 11];
    i = i + 13;

    now.RMC.Longitude.dd = (code[i] - '0') * 100 + (code[i + 1] - '0') * 10 + (code[i + 2] - '0');
    now.RMC.Longitude.mm_int = (code[i + 3] - '0') * 10 + (code[i + 4] - '0');
    now.RMC.Longitude.mm_decimal = (code[i + 6] - '0') * 10000 + (code[i + 7] - '0') * 1000 + (code[i + 8] - '0') * 100 + (code[i + 9] - '0') * 10 + (code[i + 10] - '0');
    now.RMC.Longitude.mm_data = now.RMC.Longitude.mm_decimal;
    now.RMC.Longitude.mm_data /= 100000;
    now.RMC.Longitude.mm_data += now.RMC.Longitude.mm_int;
    now.RMC.Longitude.data = now.RMC.Longitude.dd + now.RMC.Longitude.mm_data / 60;
    now.RMC.Longitude.hs = code[i + 12];
    i = i + 14;

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i++;
    temp[ptemp] = 0;
    now.RMC.GND_speed = atof(temp);

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i++;
    temp[ptemp] = 0;
    now.RMC.GND_heading = atof(temp);

    now.RMC.UTC_D_dd = (code[i] - '0') * 10 + (code[i + 1] - '0');
    now.RMC.UTC_D_mm = (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    now.RMC.UTC_D_yy = (code[i + 4] - '0') * 10 + (code[i + 5] - '0');
    i = i + 7;

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i++;
    temp[ptemp] = 0;
    now.RMC.MEG_deg = atof(temp);

    if (code[i] != ',')
    {
      now.RMC.MEG_dir = code[i];
      i++;
    }
    i++;

    now.RMC.GPS_mode = code[i];
    i = i + 2;

    now.RMC.Rcv_Checksum = (((code[i] >= 'A') && (code[i] <= 'F')) ? (code[i] - 'A' + 10) : (code[i] - '0')) * 16 + (((code[i + 1] >= 'A') && (code[i + 1] <= 'F')) ? (code[i + 1] - 'A' + 10) : (code[i + 1] - '0'));
    now.RMC.Cal_Checksum = 0;
    for (int counter = 0; counter < i - 1; counter++)
    {
      now.RMC.Cal_Checksum ^= code[counter];
    }
    return 4;
  }


  if (check_str(code, "GPVTG", 0, 0, 5))
  {
    i = 6;

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i = i + 3;
    temp[ptemp] = 0;
    now.VTG.NRH_real = atoi(temp);

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i = i + 3;
    temp[ptemp] = 0;
    now.VTG.NRH_meg = atoi(temp);

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i = i + 3;
    temp[ptemp] = 0;
    now.VTG.GND_speed_knot = atof(temp);

    ptemp = 0;
    while (code[i] != ',')
    {
      temp[ptemp] = code[i];
      i++;
      ptemp++;
    }
    i = i + 3;
    temp[ptemp] = 0;
    now.VTG.GND_speed_kmh = atof(temp);

    now.VTG.GPS_mode = code[i];
    i = i + 2;

    now.VTG.Rcv_Checksum = (((code[i] >= 'A') && (code[i] <= 'F')) ? (code[i] - 'A' + 10) : (code[i] - '0')) * 16 + (((code[i + 1] >= 'A') && (code[i + 1] <= 'F')) ? (code[i + 1] - 'A' + 10) : (code[i + 1] - '0'));
    now.VTG.Cal_Checksum = 0;
    for (int counter = 0; counter < i - 1; counter++)
    {
      now.VTG.Cal_Checksum ^= code[counter];
    }
    return 5;
  }

  if (check_str(code, "GPGLL", 0, 0, 5))
  {
    i = 6;

    now.GLL.Latitude.dd = (code[i] - '0') * 10 + (code[i + 1] - '0');
    now.GLL.Latitude.mm_int = (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    now.GLL.Latitude.mm_decimal = (code[i + 5] - '0') * 10000 + (code[i + 6] - '0') * 1000 + (code[i + 7] - '0') * 100 + (code[i + 8] - '0') * 10 + (code[i + 9] - '0');
    now.GLL.Latitude.mm_data = now.GLL.Latitude.mm_decimal;
    now.GLL.Latitude.mm_data /= 100000;
    now.GLL.Latitude.mm_data += now.GLL.Latitude.mm_int;
    now.GLL.Latitude.data = now.GLL.Latitude.dd + now.GLL.Latitude.mm_data / 60;
    now.GLL.Latitude.hs = code[i + 11];
    i = i + 13;

    now.GLL.Longitude.dd = (code[i] - '0') * 100 + (code[i + 1] - '0') * 10 + (code[i + 2] - '0');
    now.GLL.Longitude.mm_int = (code[i + 3] - '0') * 10 + (code[i + 4] - '0');
    now.GLL.Longitude.mm_decimal = (code[i + 6] - '0') * 10000 + (code[i + 7] - '0') * 1000 + (code[i + 8] - '0') * 100 + (code[i + 9] - '0') * 10 + (code[i + 10] - '0');
    now.GLL.Longitude.mm_data = now.GLL.Longitude.mm_decimal;
    now.GLL.Longitude.mm_data /= 100000;
    now.GLL.Longitude.mm_data += now.GLL.Longitude.mm_int;
    now.GLL.Longitude.data = now.GLL.Longitude.dd + now.GLL.Longitude.mm_data / 60;
    now.GLL.Longitude.hs = code[i + 12];
    i = i + 14;

    now.GLL.UTC_hh = (code[i] - '0') * 10 + (code[i + 1] - '0');
    now.GLL.UTC_mm = (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    now.GLL.UTC_ss = (code[i + 4] - '0') * 10 + (code[i + 5] - '0');
    now.GLL.UTC_ms = (code[i + 7] - '0') * 10 + (code[i + 8] - '0');
    i = i + 10;

    now.GLL.GPS_status = code[i];
    i = i + 2;

    now.GLL.GPS_mode = code[i];
    i = i + 2;

    now.GLL.Rcv_Checksum = (((code[i] >= 'A') && (code[i] <= 'F')) ? (code[i] - 'A' + 10) : (code[i] - '0')) * 16 + (((code[i + 1] >= 'A') && (code[i + 1] <= 'F')) ? (code[i + 1] - 'A' + 10) : (code[i + 1] - '0'));
    now.GLL.Cal_Checksum = 0;
    for (int counter = 0; counter < i - 1; counter++)
    {
      now.GLL.Cal_Checksum ^= code[counter];
    }
    return 6;
  }

  if (check_str(code, "GPZDA", 0, 0, 5))
  {
    i = 6;

    now.ZDA.UTC_hh = (code[i] - '0') * 10 + (code[i + 1] - '0');
    now.ZDA.UTC_mm = (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    now.ZDA.UTC_ss = (code[i + 4] - '0') * 10 + (code[i + 5] - '0');
    now.ZDA.UTC_ms = (code[i + 7] - '0') * 10 + (code[i + 8] - '0');
    i = i + 10;

    now.ZDA.UTC_D_dd = (code[i] - '0') * 10 + (code[i + 1] - '0');
    i = i + 3;

    now.ZDA.UTC_D_mm = (code[i] - '0') * 10 + (code[i + 1] - '0');
    i = i + 3;

    now.ZDA.UTC_D_yy = (code[i] - '0') * 1000 + (code[i + 1] - '0') * 100 + (code[i + 2] - '0') * 10 + (code[i + 3] - '0');
    i = i + 5;

    now.ZDA.LOC_hh = (code[i] - '0') * 10 + (code[i + 1] - '0');
    i = i + 3;

    now.ZDA.LOC_mm = (code[i] - '0') * 10 + (code[i + 1] - '0');
    i = i + 3;

    now.ZDA.Rcv_Checksum = (((code[i] >= 'A') && (code[i] <= 'F')) ? (code[i] - 'A' + 10) : (code[i] - '0')) * 16 + (((code[i + 1] >= 'A') && (code[i + 1] <= 'F')) ? (code[i + 1] - 'A' + 10) : (code[i + 1] - '0'));
    now.ZDA.Cal_Checksum = 0;
    for (int counter = 0; counter < i - 1; counter++)
    {
      now.ZDA.Cal_Checksum ^= code[counter];
    }
    return 7;
  }

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



