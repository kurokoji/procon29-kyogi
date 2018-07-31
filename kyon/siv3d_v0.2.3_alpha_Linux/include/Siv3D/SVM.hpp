﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <array>
# include "Fwd.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "../ThirdParty/libsvm/svm.h"

namespace s3d
{
	namespace SVM
	{
		using Paramter = svm_parameter;

		using Label = double;

		inline Paramter DefaultParameter(size_t maxIndex)
		{
			Paramter param;
			param.svm_type		= C_SVC;
			param.kernel_type	= RBF;
			param.degree		= 3;
			param.gamma			= 1.0 / maxIndex;
			param.coef0			= 0;
			param.nu			= 0.5;
			param.cache_size	= 100;
			param.C				= 1;
			param.eps			= 1e-3;
			param.p				= 0.1;
			param.shrinking		= 1;
			param.probability	= 0;
			param.nr_weight		= 0;
			param.weight_label	= nullptr;
			param.weight		= nullptr;

			return param;
		}

		template <size_t _Dimensions>
		struct SupportVector
		{
			static constexpr int32 Dimensions = _Dimensions;

			Label label;

			std::array<double, Dimensions> vector;
		};

		struct SparseSupportVector
		{
			Label label;

			Array<std::pair<int32, double>> vector;
		};

		class Problem
		{
		private:

			class CProblem;

			std::shared_ptr<CProblem> pImpl;

		public:

			Problem();

			template <size_t Dimensions>
			Problem(const Array<SupportVector<Dimensions>>& supportVectors)
				: Problem()
			{
				load(supportVectors);
			}

			Problem(const double* pSupportVectors, size_t num_dataset, size_t dimensions);

			Problem(const Array<SparseSupportVector>& supportVectors);

			Problem(const FilePath& path);

			~Problem();

			template <size_t Dimensions>
			bool load(const Array<SupportVector<Dimensions>>& supportVectors)
			{
				release();

				if (supportVectors.isEmpty())
				{
					return false;
				}

				return load(&supportVectors[0].label, supportVectors.size(), Dimensions);
			}

			bool load(const double* pSupportVectors, size_t num_dataset, size_t dimensions);

			bool load(const Array<SparseSupportVector>& supportVectors);

			bool load(const FilePath& path);

			void release();

			explicit operator bool() const;

			bool hasData() const;

			size_t num_SVs() const;

			int32 getMaxIndex() const;

			bool trainAndSaveModel(const FilePath& path, const Paramter& param) const;

			PredictModel trainAndCreateModel(const Paramter& param) const;
		};

		class PredictModel
		{
		private:

			class CPredictModel;

			std::shared_ptr<CPredictModel> pImpl;

		public:

			PredictModel();

			PredictModel(const FilePath& path);

			PredictModel(std::unique_ptr<svm_model*>&& ppModel);

			~PredictModel();
			explicit operator bool() const;

			bool hasData() const;

			bool load(const FilePath& path);

			void release();

			size_t num_classes() const;

			Array<int32> getLabels() const;

			Label predict(const Array<double>& vector) const;

			Label predict(const Array<std::pair<int32, double>>& vector) const;

			Label predictProbability(const Array<double>& vector, Array<double>& probabilities) const;

			Label predictProbability(const Array<std::pair<int32, double>>& vector, Array<double>& probabilities) const;
		};

		SparseSupportVector ParseSVMLight(StringView view);

		Array<SparseSupportVector> LoadSVMLight(const FilePath& path);

		bool SaveSVMLight(const FilePath& path, const Array<SparseSupportVector>& vector);

		double CalculateAccuracy(const PredictModel& model, const Array<SparseSupportVector>& testData);
	}

	void Formatter(FormatData& formatData, const SVM::SparseSupportVector& value);
}
