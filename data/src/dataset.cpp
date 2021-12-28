#include "dataset.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <string>
#include <torch/csrc/autograd/generated/variable_factories.h>
#include <torch/serialize/input-archive.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <torch/types.h>
#include <filesystem>
#include <iostream>
#include "voc_xml_data_model.h"
#include "parse.h"
#include <vector>
namespace fs = std::filesystem;
namespace
{
	constexpr int KRows = 500;
	constexpr int KCols = 375;

	torch::Tensor CVtoTensor(cv::Mat img)
	{
		cv::resize(img, img, cv::Size{KRows, KCols}, 0, 0, cv::INTER_LINEAR);
		cv::cvtColor(img, img, cv::COLOR_RGB2BGR);
		auto img_tensor = torch::from_blob(img.data, {KRows, KCols, 3}, torch::kByte);
		img_tensor = img_tensor.permute({2, 0, 1}).toType(torch::kFloat);
		return img_tensor;
	}

	std::vector<std::string> txt_to_vec(const std::string &txt_path)
	{
		std::ifstream file;
		std::vector<std::string> result;
		file.open(txt_path, std::ios_base::in);
		if (file.is_open())
		{
			std::string xml_file_name;
			std::getline(file, xml_file_name);
			result.push_back(xml_file_name);
		}
		return result;
	}
	std::pair<torch::Tensor, torch::Tensor> CovDataset::read_data(std::string data_xml_files, const std::string file_splited_path,size_t index)
	{
		std::string attribute(".jpg");
		const auto num_sample = CovDataset::xml_files_name.size();
		
		const auto annotation = CovDataset::parse.parse(data_xml_files + CovDataset::xml_files_name.at(index));
		auto image=CVtoTensor(cv::imread(annotation.filename));
		auto target=torch::Tensor();
		return {image, target};
	}
	CovDataset::CovDataset(const std::string data_xml_files, const std::string file_splited_path, Mode mode)
		: mode_(mode)
	{
		CovDataset::xml_files_name= mode == Mode::Train ? txt_to_vec(file_splited_path + "train.txt") : txt_to_vec(file_splited_path + "test.txt");
	}

	torch::data::Example<> CovDataset::get(size_t index)
	{
		auto result=CovDataset::read_data("","",index);
		return {result.first,result.second};
	}

}
