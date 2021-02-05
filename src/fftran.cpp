#include <clear.hpp>
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

struct Video {
  bool copy = false;
  bool ishave = true;
  int bitrate = 5500; // int bitrate = 2000;
  float level = 4.1;
  std::string preset = "slow";
  std::string profile = "main";
  std::string encoder = "h264";
  std::string pixFmt = "yuv420p";
};

struct Audio {
  bool copy = false;
  bool ishave = true;
  int bitrate = 320;
  float audioChannel = 2;
  int audioSampleRate = 44100;
  std::string encoder = "aac";
};

int tranTimes = 1;

void PrintLOGO();
std::string PrintCommand(struct Video *video, struct Audio *audio,
                         const char *inputFile, const char *outputFile,
                         bool CLIOUTPUT);

void MainUi(struct Video *video, struct Audio *audio);

void VideoUi(struct Video *stc);
void PrintVideo(struct Video *stc);
void VideoBitRateUI(struct Video *stc);
void VideoProfileUI(struct Video *stc);
void VideoEncoderUI(struct Video *stc);

void AudioUi(struct Audio *stc);
void PrintAudio(struct Audio *stc);
void AudioBitrateUi(struct Audio *stc);
void AudioEncoderUi(struct Audio *stc);
void AudioChannelUi(struct Audio *stc);
void AudioSanpleRateUi(struct Audio *stc);

void Execute(struct Video *vid, struct Audio *aud);
std::vector<std::string> GetFiles(const char &path);

int main(int argc, char *argv[]) {
  struct Video *video = new struct Video;
  struct Audio *audio = new struct Audio;

  clear();

  PrintLOGO();
  PrintCommand(video, audio, "InPutFile", "OutPutFile", true);
  MainUi(video, audio);

  return 0;
}

void PrintLOGO() {
  std::cout << " ########## ########## ########## ##         ##            ##\n"
            << " #########  #########   ######## ####       ####          ## \n"
            << " ##         ##             ##      ##      ##  ##        ##  \n"
            << " #######    #######        ##     ##      ##    ##      ##   \n"
            << " ######     ######         ##  ####      ###    ###    ##    \n"
            << " ##         ##             ##   ##      ##  ####  ##  ##     \n"
            << " ##         ##             ##    ##    ##          ####      \n"
            << " #          #              ##     ##  ##            ##       \n"
            << "Written By: CSQ(Circle-Square)\n";
}

std::string PrintCommand(struct Video *video, struct Audio *audio,
                         const char *inputFile, const char *outputFile,
                         bool CLIOUTPUT) {
  char temp[10];
  std::string commandLine;
  commandLine.append("ffmpeg -i ");
  commandLine.append(inputFile);

  // Video
  //--------------------------------------
  if (video->ishave) {
    if (!video->copy) {
      // Coder
      commandLine.append(" -c:v ");
      commandLine.append(video->encoder);

      // Bit rate
      commandLine.append(" -b:v ");
      commandLine.append(std::to_string(video->bitrate));

      // Level
      commandLine.append(" -level ");
      std::sprintf(temp, "%.1f", video->level);
      commandLine.append(temp);

      // Preset
      commandLine.append(" -preset ");
      commandLine.append(video->preset);

      // Profile
      commandLine.append(" -profile:v ");
      commandLine.append(video->profile);

      // Pixel Format
      commandLine.append(" -pix_fmt ");
      commandLine.append(video->pixFmt);

    } else
      commandLine.append(" -c:v copy");
  }

  // Audio
  //--------------------------------------
  if (audio->ishave) {
    if (!audio->copy) {
      // Coder
      commandLine.append(" -c:a ");
      commandLine.append(audio->encoder);

      // Bit Rate
      commandLine.append(" -b:a ");
      commandLine.append(std::to_string(audio->bitrate));

      // Audio Channel
      commandLine.append(" -ac ");
      if (audio->audioChannel - (int)(audio->audioChannel / 1.0) == 0)
        sprintf(temp, "%1.0f", audio->audioChannel);
      else
        sprintf(temp, "%.1f", audio->audioChannel);
      commandLine.append(temp);

      // Audio Sample Rate
      commandLine.append(" -ar ");
      commandLine.append(std::to_string(audio->audioSampleRate));
    } else
      commandLine.append(" -c:a copy");
  }

  commandLine.append(" ");
  commandLine.append(outputFile);
  if (CLIOUTPUT)
    std::cout << "Command Line : " << commandLine.c_str() << std::endl;

  return commandLine;
}

void MainUi(struct Video *video, struct Audio *audio) {
  std::cout << "\n"
            << "    ...:::: Main Menu ::::...\n"
            << "\t1. Video Seetings\n"
            << "\t2. Audio Seetings\n"
            << "\tE. Execute\n"
            << "\tQ. Exit\n"
            << "    ---==== Main Menu ====---\n";
  if (video->ishave) {
    if (video->copy) {
      std::cout << "Video: Copy stream!\n";
    } else {
      std::cout << "Video: Encoder" << video->encoder << std::endl;
      printf("\tBitRate: %5d Level: %.1f\n Color_format: %s", video->bitrate,
             video->level, video->pixFmt.c_str());
    }
  } else
    std::cout << "Video : Close!\n";

  if (audio->ishave) {
    if (audio->copy) {
      std::cout << "Audio: Copy stream!\n";
    } else {
      std::cout << "Audio: Encoder: " << audio->encoder << std::endl;
      printf("\tBitRate: %3d AudioChannel: %.1f AudioSampleRate: %5d",
             audio->bitrate, audio->audioChannel, audio->audioSampleRate);
    }
  } else
    std::cout << "Aideo : Close!\n";
}

void PrintAudio(struct Audio * stc){
  if (stc->ishave) {
    if (stc->copy) {
      std::cout << "Audio: Copy stream!\n";
    } else {
      std::cout << "Audio: Encoder: " << stc->encoder << std::endl;
      printf("\tBitRate: %3d AudioChannel: %.1f AudioSampleRate: %5d",
             stc->bitrate, stc->audioChannel, stc->audioSampleRate);
    }
  } else
    std::cout << "Aideo : Close!\n";
}

void PrintVideo(struct Video * stc){
  if (stc->ishave) {
    if (stc->copy) {
      std::cout << "Video: Copy stream!\n";
    } else {
      std::cout << "Video: Encoder" << stc->encoder << std::endl;
      printf("\tBitRate: %5d Level: %.1f\n Color_format: %s", stc->bitrate,
             stc->level, stc->pixFmt.c_str());
    }
  } else
    std::cout << "Video : Close!\n";
}
