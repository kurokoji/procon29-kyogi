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
# include <memory>
# include "Fwd.hpp"
# include "Optional.hpp"
# include "AssetHandle.hpp"
# include "Wave.hpp"
# include "Duration.hpp"
# include "NamedParameter.hpp"

namespace s3d
{
	struct AudioLoopTiming
	{
		int64 beginPos = 0;

		int64 endPos = 0;

		constexpr AudioLoopTiming() noexcept
			: beginPos(0)
			, endPos(0) {}

		constexpr AudioLoopTiming(int64 _beginPos) noexcept
			: beginPos(_beginPos)
			, endPos(0) {}

		constexpr AudioLoopTiming(int64 _beginPos, int64 _endPos) noexcept
			: beginPos(_beginPos)
			, endPos(_endPos) {}
	};

	class Audio
	{
	protected:

		class Handle {};

		using AudioHandle = AssetHandle<Handle>;

		friend AudioHandle::~AssetHandle();

		std::shared_ptr<AudioHandle> m_handle;

	public:

		using IDType = AudioHandle::IDWrapperType;

		/// <summary>
		/// デフォルトコンストラクタ
		/// </summary>
		Audio();

		explicit Audio(Wave&& wave);

		Audio(Wave&& wave, const Optional<AudioLoopTiming>& loop);

		Audio(Wave&& wave, Arg::loop_<bool> loop);

		Audio(Wave&& wave, Arg::loopBegin_<uint64> loopBegin);

		Audio(Wave&& wave, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		Audio(Wave&& wave, Arg::loopBegin_<SecondsF> loopBegin);

		Audio(Wave&& wave, Arg::loopBegin_<SecondsF> loopBegin, Arg::loopEnd_<SecondsF> loopEnd);

		explicit Audio(const FilePath& path);

		Audio(const FilePath& path, const Optional<AudioLoopTiming>& loop);

		Audio(const FilePath& path, Arg::loop_<bool> loop);

		Audio(const FilePath& path, Arg::loopBegin_<uint64> loopBegin);

		Audio(const FilePath& path, Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		Audio(const FilePath& path, Arg::loopBegin_<SecondsF> loopBegin);

		Audio(const FilePath& path, Arg::loopBegin_<SecondsF> loopBegin, Arg::loopEnd_<SecondsF> loopEnd);

		//explicit Audio(IReader&& reader);

		virtual ~Audio();

		void release();

		/// <summary>
		/// オーディオが空かどうかを示します。
		/// </summary>
		bool isEmpty() const;

		/// <summary>
		/// オーディオが空ではないかを返します。
		/// </summary>
		/// <returns>
		/// オーディオが空ではない場合 true, それ以外の場合は false
		/// </returns>
		explicit operator bool() const
		{
			return !isEmpty();
		}

		IDType id() const;

		bool operator ==(const Audio& audio) const;

		bool operator !=(const Audio& audio) const;

		uint32 samplingRate() const;

		size_t samples() const;

		void setLoop(bool loop);

		void setLoop(Arg::loopBegin_<uint64> loopBegin);

		void setLoop(Arg::loopBegin_<uint64> loopBegin, Arg::loopEnd_<uint64> loopEnd);

		void setLoop(Arg::loopBegin_<SecondsF> loopBegin);

		void setLoop(Arg::loopBegin_<SecondsF> loopBegin, Arg::loopEnd_<SecondsF> loopEnd);

		bool play(const SecondsF& fadeinDuration = SecondsF(0.0)) const;

		void pause(const SecondsF& fadeoutDuration = SecondsF(0.0)) const;

		void stop(const SecondsF& fadeoutDuration = SecondsF(0.0)) const;

		void playOneShot(double volume = 1.0, double pitch = 1.0) const;

		void stopAllShots() const;

		/// <summary>
		/// サウンドが再生中であるかを返します。
		/// </summary>
		bool isPlaying() const;

		/// <summary>
		/// サウンドが一時停止中であるかを返します。
		/// </summary>
		bool isPaused() const;

		/// <summary>
		/// 再生位置（サンプル）を返します。
		/// </summary>
		int64 posSample() const;

		/// <summary>
		/// 再生バッファに送信済みのサウンドの位置（サンプル）を返します。
		/// </summary>
		int64 streamPosSample() const;

		/// <summary>
		/// ループを含めた再生済みのサンプル数を返します。
		/// </summary>
		int64 samplesPlayed() const;

		/// <summary>
		/// サウンドの長さ（秒）を返します。
		/// </summary>
		double lengthSec() const;

		/// <summary>
		/// 波形データにアクセスします。
		/// </summary>
		/// <returns>
		/// サウンドの波形データへの参照
		/// </returns>
		const Wave& getWave() const;

		/// <summary>
		/// 音量を変更します。
		/// </summary>
		/// <param name="volume">
		/// 音量 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setVolume(double volume) const
		{
			setVolumeLR(volume, volume);
		}

		/// <summary>
		/// 音量を変更します。
		/// </summary>
		/// <param name="left">
		/// 左チャンネルの音量 [0.0, 1.0]
		/// </param>
		/// <param name="right">
		/// 右チャンネルの音量 [0.0, 1.0]
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setVolumeLR(double left, double right) const;

		/// <summary>
		/// 音量を減衰レベル（dB）で設定します。
		/// </summary>
		/// <param name="attenuation_dB">
		/// 減衰レベル（dB） [-100, 0.0]
		/// </param>
		/// <remarks>
		/// atten. = vol.
		/// 0 dB = 1.0
		/// -6 dB = 0.5
		/// -12 dB = 0.25
		/// -18 db = 0.125
		/// </remarks>
		/// <returns>
		/// なし
		/// </returns>
		void setVolume_dB(double attenuation_dB) const
		{
			setVolumeLR_dB(attenuation_dB, attenuation_dB);
		}

		/// <summary>
		/// 音量を減衰レベル（dB）で設定します。
		/// </summary>
		/// <param name="attenuationLeft_dB">
		/// 左チャンネルの減衰レベル（dB）
		/// </param>
		/// <param name="attenuationRight_dB">
		/// 右チャンネルの減衰レベル（dB）
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void setVolumeLR_dB(double attenuationLeft_dB, double attenuationRight_dB) const
		{
			const double left = std::pow(10.0, attenuationLeft_dB / 20.0);
			const double right = std::pow(10.0, attenuationRight_dB / 20.0);
			setVolumeLR(left, right);
		}

		void setSpeed(double speed) const;

		void setSpeedBySemitone(int32 semitone) const;

		double getSpeed() const;

		double getMinSpeed() const;

		double getMaxSpeed() const;
	};

	using AudioID = Audio::IDType;
}
