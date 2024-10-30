#include "RecordFileHandler.h"
#include "SearchComparisonBenchmark.h"

/*
 * Pega o diretório atual onde o programa está sendo executado
 * é necessário achar o último separador de caminho (/ ou \) para remover o nome do executável
 * pode não funcionar dependendo do SO, caso ele não tenha o conceito de diretório, mas funcionará para o windows e linux.
 */
std::string GetCurrentDirectoryPath(char** argv)
{
    const std::string programPath = argv[0];
    const size_t separatorIndex = programPath.find_last_of("\\/");
    return programPath.substr(0, separatorIndex + 1);
}

/*
 * 1: Gera os arquivos aleatórios e separa as chaves para o teste
 * 2: Executa os testes em cima dos arquivos gerados
 */
int main(int argc, char* argv[])
{
    const std::string directoryPath = GetCurrentDirectoryPath(argv);

    const std::vector<RecordFileHandler> recordFileHandlers
    {
        RecordFileHandler(directoryPath, 100, false),
        RecordFileHandler(directoryPath, 500, false),
        RecordFileHandler(directoryPath, 1000, false),
        RecordFileHandler(directoryPath, 5000, false),
        RecordFileHandler(directoryPath, 10000, false),
        RecordFileHandler(directoryPath, 100, true),
        RecordFileHandler(directoryPath, 500, true),
        RecordFileHandler(directoryPath, 1000, true),
        RecordFileHandler(directoryPath, 5000, true),
        RecordFileHandler(directoryPath, 10000, true)
    };

    SearchComparisonBenchmark benchmark(recordFileHandlers);

    if(!benchmark.TryGenerateRecordFiles())
    {
        return -1;
    }

    benchmark.BenchmarkAllFiles();    
    return 0;
}
