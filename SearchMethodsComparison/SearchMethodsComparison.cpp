#include "RegisterFileHandler.h"
#include "SearchComparisonBenchmark.h"

std::string GetCurrentDirectoryPath(char** argv)
{
    const std::string programPath = argv[0];
    const size_t separatorIndex = programPath.find_last_of("\\/");
    return programPath.substr(0, separatorIndex + 1);
}

int main(int argc, char* argv[])
{
    const std::string directoryPath = GetCurrentDirectoryPath(argv);

    const std::vector<RecordFileHandler> recordFileHandlers
    {
        RecordFileHandler(directoryPath, 500, false),
        RecordFileHandler(directoryPath, 1000, false),
        RecordFileHandler(directoryPath, 10000, false),
        RecordFileHandler(directoryPath, 100, true),
        RecordFileHandler(directoryPath, 500, true),
        RecordFileHandler(directoryPath, 1000, true),
        RecordFileHandler(directoryPath, 10000, true)
    };

    SearchComparisonBenchmark<15> benchmark(recordFileHandlers);

    if(!benchmark.TryGenerateRecordFiles())
    {
        return -1;
    }

    benchmark.BenchmarkAllFiles();    
    return 0;
}
