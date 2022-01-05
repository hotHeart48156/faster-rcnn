#include "dataset.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <string>
#include <torch/serialize/input-archive.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <torch/types.h>
#include <torch/script.h>
#include <torch/torch.h>
#include <filesystem>
#include <iostream>
#include "voc_xml_data_model.h"
#include "parse.h"
#include <vector>
#include <map>
namespace fs = std::filesystem;
namespace
{
	constexpr int KRows = 500;
	constexpr int KCols = 375;

	torch::Tensor CVtoTensor(cv::Mat img)
	{
		assert(!img.empty());
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
	std::pair<torch::Tensor, torch::Tensor> CovDataset::read_data(std::string data_xml_files, const std::string file_splited_path, size_t index)
	{
		std::string attribute(".jpg");
		const auto annotation = CovDataset::parse.parse(data_xml_files + CovDataset::xml_files_name.at(index));
		auto image = CVtoTensor(cv::imread(annotation.filename));
		const int size = annotation.objects.size();
		double **boxes;
		boxes = (double **)malloc(size * sizeof(double *));
		char **labels;
		labels = (char **)malloc(size * sizeof(char *));
		int *iscrowd;
		iscrowd = (int *)malloc(size * sizeof(int));
		double *area;
		area = (double *)malloc(size * sizeof(double));

		int i = 0;
		for (auto object : annotation.objects)
		{
			double box[4] = {object.bndbox.xmax, object.bndbox.xmin, object.bndbox.ymax, object.bndbox.ymin};
			boxes[i] = box;
			labels[i] = const_cast<char *>(object.name.c_str());
			iscrowd[i] = 0;
			i++;
		}

		for (i = 0; i < size; i++)
		{
			double box_area = (boxes[i][0] - boxes[i][1]) * (boxes[i][2] - boxes[i][3]);
			area[i] = box_area;
		}
		
		
		auto boxes_tensor = torch::tensor(boxes, torch::kFloat32);
		auto labels_tensor = torch::tensor(labels, torch::kInt64);
		auto iscrowd_tensor = torch::tensor(iscrowd, torch::kInt64);
		auto area_tensor = torch::tensor(area, torch::kFloat32);
		// std::map<std::string, torch::Tensor> target;
		// auto target_it = target.begin();
		// target.insert(target_it, std::pair<std::string, torch::Tensor>("boxes", boxes_tensor));
		// target.insert(target_it, std::pair<std::string, torch::Tensor>("labels", labels_tensor));
		// target.insert(target_it, std::pair<std::string, torch::Tensor>("iscrowd", iscrowd_tensor));
		// target.insert(target_it, std::pair<std::string, torch::Tensor>("area", area_tensor));
		torch::Tensor target[4];
		// target=(torch::Tensor*)malloc(4*sizeof(boxes_tensor));
		target[0]=boxes_tensor;
		target[1]=labels_tensor;
		target[2]=iscrowd_tensor;
		target[3]=area_tensor;

		return {image, boxes_tensor};
	}
	CovDataset::CovDataset(const std::string data_xml_files, const std::string file_splited_path, Mode mode)
		: mode_(mode)
	{
		CovDataset::xml_files_name = mode == Mode::Train ? txt_to_vec(file_splited_path + "train.txt") : txt_to_vec(file_splited_path + "test.txt");
	}

	Example CovDataset::get(size_t index)
	{
		auto result = CovDataset::read_data("", "", index);
		// return {result.first, result.second};
		// return{result.first,result.second};
		std::map<std::string,std::string> cc;
		return {torch::tensor(0),cc};
	}
}
