#include "dataset.h"
#include <ATen/Functions.h>
#include <c10/core/ScalarType.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <string>
#include <torch/csrc/autograd/generated/variable_factories.h>
#include <torch/serialize/input-archive.h>
#include <expat.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <torch/types.h>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;
namespace
{
	constexpr int KTrainSize = 200;
	constexpr int KTestSize = 200;
	constexpr int KRows = 300;
	constexpr int KCols = 300;

	torch::Tensor CVtoTensor(cv::Mat img)
	{
		cv::resize(img, img, cv::Size{KRows, KCols}, 0, 0, cv::INTER_LINEAR);
		cv::cvtColor(img, img, cv::COLOR_RGB2BGR);
		auto img_tensor = torch::from_blob(img.data, {KRows, KCols, 3}, torch::kByte);
		img_tensor = img_tensor.permute({2, 0, 1}).toType(torch::kFloat);
		return img_tensor;
	}
	std::pair<torch::Tensor, torch::Tensor> read_data(const std::string &root, bool train)
	{
		int i = 0;
		std::string attribute(".jpg");
		const auto num_sample = train ? KTrainSize : KTestSize;
		const auto folder = train ? "/train" : "/test";
		auto targets = torch::empty(num_sample, torch::kFloat);
		auto images = torch::empty({num_sample, 3, KRows, KCols}, torch::kFloat);
		for (const auto &p : fs::directory_iterator(folder))
		{
			if (p.path().extension() == attribute)
			{
				cv::Mat img = cv::imread(p.path());
				auto img_tensor = CVtoTensor(img);
				// targets[i]=torch::tensor(targets,torch::kFloat64);
				// fopen
			}
		}
		return {images, targets};
	}
	CovDataset::CovDataset(const std::string &root, Mode mode):mode_(mode)
	{
		auto data = read_data(root, mode = Mode::Train);
		auto image = std::move(data.first);
		auto targets = std::move(data.second);
	}

	torch::data::Example<> CovDataset::get(size_t index)
	{
		return {images_[index], targets_[index]};
	}

	torch::optional<size_t> CovDataset::size() const {
		return images_.size(0);
	}
}
