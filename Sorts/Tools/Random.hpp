#pragma once
#include <random>
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>

template<class _ValTy>
    requires std::integral<_ValTy> || std::_Is_any_of_v<std::remove_cv_t<_ValTy>, float, double>
class Rand_Uniform
{
public:
    explicit Rand_Uniform() = default;
    Rand_Uniform& operator()(const Rand_Uniform&) = delete;

public:
    inline _ValTy operator()(double min, double max) const
    {
        if (m_distribution == nullptr || m_distribution->min() != min || m_distribution->max() != max) {
            m_distribution = new std::uniform_real_distribution<double>(min, max);
        }
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    std::vector<_ValTy> generateVec(size_t size, double min, double max, const std::string& saveLocation = "") const
    {
        std::vector<_ValTy> vec;
        std::uniform_real_distribution<double> distribution(min, max);
        std::ofstream outFile(saveLocation);
        while (size--) {
            vec.push_back((_ValTy)distribution(m_engine));
            if (outFile.is_open()) {
                outFile << vec.back() << ",";
            }
        }
        if (outFile.is_open()) {
            outFile.seekp(-1, std::ios_base::end);
            outFile.put(' ');
            outFile.close();
        }
        return vec;
    }

private:
    static std::random_device _rd;
    static thread_local std::default_random_engine m_engine;
    static std::uniform_real_distribution<double>* m_distribution;
};

template<class _ValTy>
    requires std::integral<_ValTy> || std::_Is_any_of_v<std::remove_cv_t<_ValTy>, float, double>
std::random_device Rand_Uniform<_ValTy>::_rd{};

template<class _ValTy>
    requires std::integral<_ValTy> || std::_Is_any_of_v<std::remove_cv_t<_ValTy>, float, double>
thread_local std::default_random_engine Rand_Uniform<_ValTy>::m_engine{ _rd() };

template<class _ValTy>
    requires std::integral<_ValTy> || std::_Is_any_of_v<std::remove_cv_t<_ValTy>, float, double>
std::uniform_real_distribution<double>* Rand_Uniform<_ValTy>::m_distribution{nullptr};

template<class _ValTy>
    requires std::integral<_ValTy> || std::_Is_any_of_v<std::remove_cv_t<_ValTy>, float, double>
class Rand_Normal
{
public:
    inline _ValTy operator()(double mean, double sigma) const
    {
        if (m_distribution == nullptr || m_distribution->mean() != mean || m_distribution->sigma() != sigma) {
            m_distribution = new std::normal_distribution<double>(mean, sigma);
        }
        return static_cast<_ValTy>(m_distribution->operator()(m_engine));
    }

    std::vector<_ValTy> generateVec(size_t size, double mean, double sigma, const std::string& saveLocation = "") const
    {
        std::vector<_ValTy> vec;
        std::normal_distribution<double> distribution(mean, sigma);
        std::ofstream outFile(saveLocation);
        while (size--) {
            vec.push_back(_ValTy(distribution(m_engine)));
            if (outFile.is_open()) {
                outFile << vec.back() << ",";
            }
        }
        if (outFile.is_open()) {
            outFile.seekp(-1, std::ios_base::end);
            outFile.put(' ');
            outFile.close();
        }
        return vec;
    }

private:
    static std::random_device _rd;
    static thread_local std::default_random_engine m_engine;
    static std::normal_distribution<double>* m_distribution;
};

template<class _ValTy>
    requires std::integral<_ValTy> || std::_Is_any_of_v<std::remove_cv_t<_ValTy>, float, double>
std::random_device Rand_Normal<_ValTy>::_rd{};

template<class _ValTy>
    requires std::integral<_ValTy> || std::_Is_any_of_v<std::remove_cv_t<_ValTy>, float, double>
thread_local std::default_random_engine Rand_Normal<_ValTy>::m_engine{ _rd() };

template<class _ValTy>
    requires std::integral<_ValTy> || std::_Is_any_of_v<std::remove_cv_t<_ValTy>, float, double>
std::normal_distribution<double>* Rand_Normal<_ValTy>::m_distribution{ nullptr };

template<class _ValTy>
class DistributionVisualizer
{
public:
    explicit DistributionVisualizer() = default;
    DistributionVisualizer& operator=(const DistributionVisualizer&) = delete;
public:
    void operator()(
        const std::vector<_ValTy>& randVec,
        const size_t binNum = 10,
        const size_t maxStarNum = 15
        ) const
    {
        if (randVec.empty()) return;
        _ValTy minElem = *std::ranges::min_element(randVec);
        _ValTy maxElem = *std::ranges::max_element(randVec);
        _ValTy range = maxElem - minElem;

        if (range == 0) {
            std::cout << "All the elements are: " << maxElem << std::endl;
            return;
        }

        double average = std::accumulate(randVec.begin(), randVec.end(), 0.0) / randVec.size();
        std::vector<size_t> bins(binNum);

        std::cout << "min: " << minElem << " max: " << maxElem << " average: " << average << std::endl;

        for (const auto& val : randVec) {
            size_t bin = static_cast<size_t>(double(val - minElem) / range * binNum);
            if (bin == bins.size()) { bin -= 1; }
            ++bins[bin];
        }
        size_t maxS = *std::ranges::max_element(bins);
        double resizer = double(maxS) / maxStarNum;
        for (auto& val : bins) {
            val = (size_t)ceil(val / resizer);
        }
        for (size_t i = 0; i < bins.size(); ++i) {
            std::cout << i << ": ";
            for (size_t j = 0; j < bins[i]; ++j) {
                std::cout << "*";
            }
            std::cout << std::endl;
        }
        return;
    }
};