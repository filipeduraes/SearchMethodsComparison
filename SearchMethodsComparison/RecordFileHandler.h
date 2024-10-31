#pragma once
#include <array>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "ISearchableSet.h"

/*
 * Registro que guarda os dados usados nos testes (dado1 (valor inteiro), dado2 (char[1000])
 * Foi usado uma std::string para facilitar na manipulação dos dados, porém o tamanho continua sendo 1000
 */
struct Record
{
    int firstData;
    std::string secondData;
    
    Record(const int firstData, std::string secondData)
        : firstData(firstData), secondData(std::move(secondData))
    {
    }
};

/*
 * Guarda um par com a chave do nó e o registro guardado por ele
 * Foi feito dessa forma ao invés de usar um std::map para facilitar na randomização e na ordenação, já que o std::map não possui indexação
 * O registro é um std::unique_ptr para não precisar ser liberado manualmente, assim que RecordKeyPair for liberado, ele também será liberado 
 */
struct RecordKeyPair
{
    int key;
    std::unique_ptr<Record> record;

    RecordKeyPair(const int key, std::unique_ptr<Record> record)
        : key(key), record(std::move(record))
    {
    }
};

/*
 * Guarda as chaves aleatórias geradas pelo RecordFileHandler (presentes e não presentes)
 */
struct RandomRecordKeys
{
    std::vector<int> presentKeys;
    std::vector<int> notPresentKeys;

    RandomRecordKeys() = default;

    RandomRecordKeys(const std::vector<int>& presentKeys, const std::vector<int>& notPresentKeys)
        : presentKeys(presentKeys), notPresentKeys(notPresentKeys)
    {
    }
};

/*
 * Gera e lê os arquivos com registros aleatórios no formato: chave,dado1,dado2
 * Gera e deixa guardado as chaves aleatórias (presentes e não presentes) logo após gerar os arquivos
 */
class RecordFileHandler
{
private:
    std::string directory;
    RandomRecordKeys randomKeys;
    int recordCount;
    int randomKeysLength;
    bool isSorted;
    
public:
    RecordFileHandler(std::string fileDirectory, const int recordCount, const bool isOrdered = false, const int randomKeysLength = 15)
        : directory(std::move(fileDirectory))
        , recordCount(recordCount)
        , randomKeysLength(randomKeysLength)
        , isSorted(isOrdered)
    {
    }

    int GetRecordCount() const
    {
        return recordCount;
    }

    bool GetIsSorted() const
    {
        return isSorted;
    }
    
    RandomRecordKeys GetRandomKeysFromFile()
    {
        return randomKeys;
    }
    bool CompareKeys(const RecordKeyPair& a, const RecordKeyPair& b)
    {
        return a.key < b.key;
    }
    
    std::string GenerateFile();
    void PopulateSetsWithFile(const std::vector<ISearchableSet<int, std::shared_ptr<Record>>*>& sets) const;
    
private:
    std::string GetFilePath() const;
    void GenerateRandomRecordsWithKey(std::vector<RecordKeyPair>& records);
    static Record GenerateRandomRecord();

    void GenerateRandomKeys(std::unordered_set<int> alreadyUsedKeys);
    static void FillNotPresentKeys(std::unordered_set<int>& keys, std::vector<int>& notPresentKeys);
    static void FillPresentKeys(std::unordered_set<int>& keys, std::vector<int>& presentKeys);
};