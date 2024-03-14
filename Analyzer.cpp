#include <Analyzer.h>

Analyzer::Analyzer(string ping_results_file, string short_iperf_file, string long_iperf_file)
{
    this->ping_results = ping_results_file;
    this->short_iperf_results = short_iperf_file;
    this->long_iperf_results = long_iperf_file;
}

bool Analyzer::analyze(uint8_t OP_CODE)
{
    switch(OP_CODE){
        case PING_SERVER:
            return ping_test();
            break;
        case SHORT_IPERF:
            return iperf_test(this->short_iperf_results);
            break;
        case LONG_IPERF:
            return iperf_test(this->long_iperf_results);
            break;
        default:
            return false;
    };
}

bool Analyzer::ping_test()
{
    string line;
    string sub = "packets received";
    int found = 0;
    fstream fp;
    fp.open(this->ping_results);
    while(getline(fp, line))
    {
        if((found=line.find(sub))!=string::npos)
        {
            if(stoi(string(1,line[found-2])))
            {
                fp.close();
                remove(this->ping_results.c_str());
                return true;
            }
            
        }
    }
    fp.close();
    remove(this->ping_results.c_str());
    return false;
}

bool Analyzer::iperf_test(string file_name)
{
    string line;
    fstream fp;
    string sub = "Lost";
    fp.open(file_name);
    while(getline(fp, line))
    {
        if(line.find(sub)!=string::npos)
        {
            getline(fp, line);
            string bitrate_sub = "Mbits/sec";
            int found = line.find(bitrate_sub);
            string bitrate = line.substr(found-5, 4);
            float f_bitrate = stof(bitrate);
            cout << "Sender Bitrate: " << f_bitrate <<endl;
            fp.close();
            remove(file_name.c_str());
            if(f_bitrate > 40.0)
            {
                return true;
            }
            else
            {
                break;
            }
        }
    }
    fp.close();
    remove(file_name.c_str());
    return false;
}