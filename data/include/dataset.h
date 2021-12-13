#include <string>
#include <torch/torch.h>
enum Mode
{
    Train,
    Test
};
namespace {
struct CovDataset : torch::data::Dataset<CovDataset>
{
private:
    torch::Tensor images_;
    torch::Tensor targets_;
    Mode mode_;

public:
    explicit CovDataset(const std::string &root, Mode mode = Mode::Train);
    torch::data::Example<> get(size_t index) override;
    torch::optional<size_t> size() const override;
    // return image and labels
    const torch::Tensor &images() const;
    const torch::Tensor $targets() const;
};

};