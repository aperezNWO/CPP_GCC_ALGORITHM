///////////////////////////////////////////////////////////////////////////
// REGEX MANAGER
///////////////////////////////////////////////////////////////////////////

#include "RegExManager.h"

//
RegExManager::RegExManager()
{
	this->GetXml();
}
//
RegExManager::~RegExManager()
{
	//
}
//
int RegExManager::GetXml()
{
	//
	string filePath        = this->configMap["XMLPATH"];

	// Open the file
	std::ifstream inputFile(filePath);

	// Check if the file is successfully opened
	if (!inputFile.is_open()) {
		std::cerr << "Error opening file: " << filePath << std::endl;
		return 1; // Return an error code
	}

	// Read and print the contents of the file
	std::string line;
	while (std::getline(inputFile, line))
	{
		//
		this->xmlItems.push_back(line);
	}

	// Close the file
	inputFile.close();

	//
	return 0;
}
//
string RegExManager::RegExEval(char* p_tagSearch, char* p_textSearch)
{
		//
		int matchCount        = 0;
		string textMatch      = "";
		string _p_tagSearch   = StringTrim(p_tagSearch);
		string _p_textSearch  = StringTrim(p_textSearch);
		//
		std::ostringstream oss_regex;
		//
		oss_regex << "((<" << _p_tagSearch << ".*>)(.*" << _p_textSearch << ".*)(<\/" << _p_tagSearch << ">))";
		//
		string strRegex    = oss_regex.str();
		//
		std::regex regexExp(strRegex, std::regex_constants::icase);
		//
		std::smatch regexMatch;
		//
		for (auto _xmlItem = this->xmlItems.begin(); _xmlItem != this->xmlItems.end(); ++_xmlItem) {
			//
			stringstream  ss;
			//
			ss << *_xmlItem;
			//
			string xmlItem     = ss.str();
			//
			if (std::regex_search(xmlItem, regexMatch, regexExp)) {
				//
				string openingTag = "<"  + _p_tagSearch + ">";
				string closingTag = "</" + _p_tagSearch + ">";
				//
				xmlItem.replace(xmlItem.find(openingTag) ,openingTag.length(), "[" + openingTag);
				xmlItem.replace(xmlItem.find(closingTag) ,closingTag.length(), closingTag + "]");
				//
				matchCount++;
			}
			//
			textMatch += (xmlItem + '\n');
		}
	//
	string encodedTextMatch = HtmlEncode(textMatch);
	//
	std::ostringstream oss_result;
	//
	oss_result << std::to_string(matchCount) << "|" << encodedTextMatch << "|" << strRegex << std::endl;
	//
	return oss_result.str();
}
