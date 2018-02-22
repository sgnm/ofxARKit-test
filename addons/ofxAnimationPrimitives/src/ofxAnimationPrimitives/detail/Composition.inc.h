
inline Composition::Duration::Duration(float total_duration)
	: fadein_duration(0)
	, total_duration(total_duration)
	, fadeout_duration(0)
{
	
}

inline Composition::Duration::Duration(float fadein_duration, float total_duration, float fadeout_duration)
	: fadein_duration(fadein_duration)
	, total_duration(total_duration)
	, fadeout_duration(fadeout_duration)
{
}


#pragma mark - Composition

inline Composition::Composition()
	: state(PAUSED)
	, alpha(0)
	, alpha_delta(0)
	, elapsed_time(0)
	, duration(0, 0, 0)
{
}

inline Composition::~Composition()
{
	if (isPlaying())
	{
		_viewWillAppear();
		_viewDidAppear();
	}
}

template <typename T>
inline Composition::Ref Composition::New()
{
	return Composition::Ref(new T);
}

/*
http://nedbatchelder.com/code/cog/
$ cog.py -r SomoSourceCode.h

[[[cog
import cog

tmpl = '''template <typename T, %(A)s>
inline Composition::Ref Composition::New(%(B)s)
{
	return Composition::Ref(new T(%(C)s));
}
'''

cog.outl('')
for i in xrange(1, 18):
	a = ', '.join(['typename A%i' % x for x in range(i)])
	b = ', '.join(['const A%i& a%i' % (x, x) for x in range(i)])
	c = ', '.join(['a%i' % x for x in range(i)])
	cog.outl(tmpl % {'A':a, 'B':b, 'C':c})

]]]*/

template <typename T, typename A0>
inline Composition::Ref Composition::New(const A0& a0)
{
	return Composition::Ref(new T(a0));
}

template <typename T, typename A0, typename A1>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1)
{
	return Composition::Ref(new T(a0, a1));
}

template <typename T, typename A0, typename A1, typename A2>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2)
{
	return Composition::Ref(new T(a0, a1, a2));
}

template <typename T, typename A0, typename A1, typename A2, typename A3>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3)
{
	return Composition::Ref(new T(a0, a1, a2, a3));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15));
}

template <typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
inline Composition::Ref Composition::New(const A0& a0, const A1& a1, const A2& a2, const A3& a3, const A4& a4, const A5& a5, const A6& a6, const A7& a7, const A8& a8, const A9& a9, const A10& a10, const A11& a11, const A12& a12, const A13& a13, const A14& a14, const A15& a15, const A16& a16)
{
	return Composition::Ref(new T(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16));
}

//[[[end]]]

inline float Composition::getElapsedTime() const { return elapsed_time; }
inline float Composition::getDuration() const { return duration.total_duration; }
inline float Composition::getPosition() const { return elapsed_time / (duration.total_duration + std::numeric_limits<float>::denorm_min()); }
inline float Composition::getAlpha() const { return alpha; }
inline bool Composition::isPlaying() const { return state != PAUSED && state != FINISHED; }
inline bool Composition::isFinished() const { return state == FINISHED; }

inline void Composition::reset()
{
	CompositionRunner::defaultRunner().unregisterComposition(this);
	
	state = PAUSED;
	elapsed_time = 0;
	alpha = 0;
	alpha_delta = 0;
	
	{
		multimap<Trigger, Composition::Ref>::iterator it = trigger_event_map.begin();
		while (it != trigger_event_map.end())
		{
			Composition::Ref &o = it->second;
			o->reset();
			it++;
		}
		
		trigger_event_map.clear();
	}
	
	{
		multimap<float, Composition::Ref>::iterator it = time_event_map.begin();
		while (it != time_event_map.end())
		{
			Composition::Ref &o = it->second;
			o->reset();
			it++;
		}
		
		time_event_map.clear();
	}
}

inline void Composition::play()
{
	if (isPlaying())
	{
		ofLogWarning("Composition") << "play method called multiple times.";
		return;
	}
	
	if (duration.fadein_duration <= 0)
	{
		alpha_delta = 1.;
		alpha = 1;
		
		updateState();
	}
	else
	{
		alpha_delta = 1. / duration.fadein_duration;
	}
	
	state = STARTED;
	
	CompositionRunner::defaultRunner().registerComposition(this);
}

inline void Composition::play(float scene_total_duration)
{
	Composition::play(0, scene_total_duration, 0);
}

inline void Composition::play(float fadein_duration, float scene_total_duration, float fadeout_duration)
{
	duration = Duration(fadein_duration, scene_total_duration, fadeout_duration);
	Composition::play();
}

inline void Composition::stop(float fadeout_duration)
{
	if (state == FADEOUT)
	{
		ofLogWarning("Composition") << "stop method called multiple times.";
		return;
	}

	if (fadeout_duration <= 0)
	{
		alpha_delta = -1;
		alpha = 0;
		
		updateState();
	}
	else
	{
		alpha_delta = -alpha / fadeout_duration;
	}
}

inline void Composition::_update(float tick)
{
	if (!isPlaying()) return;
	
	float last_elapsed_time = elapsed_time;
	elapsed_time += tick;
	alpha += alpha_delta * tick;
	
	if (state == PLAYING
		&& !isinf(duration.total_duration))
	{
		const float fadeout_time = duration.total_duration - duration.fadeout_duration;
		if (elapsed_time > fadeout_time)
		{
			stop(duration.fadeout_duration);
		}
	}
	
	updateState();
	
	procTimeEvent(last_elapsed_time, elapsed_time);
		
	if (isPlaying())
		update();
}

inline void Composition::_draw()
{
	if (!isPlaying()) return;
#ifndef TARGET_OPENGLES
	glPushAttrib(GL_ALL_ATTRIB_BITS);
#endif
	ofPushStyle();
	ofPushView();
	draw();
	ofPopView();
	ofPopStyle();
#ifndef TARGET_OPENGLES
	glPopAttrib();
#endif
}

inline void Composition::_viewWillAppear()
{
	viewWillAppear();
	
	procTriggerEvent(WILL_APPEAR);
}

inline void Composition::_viewDidAppear()
{
	viewDidAppear();
	
	procTriggerEvent(DID_APPEAR);
}

inline void Composition::_viewWillDisappear()
{
	viewWillDisappear();
	
	procTriggerEvent(WILL_DISAPPEAR);
}

inline void Composition::_viewDidDisappear()
{
	viewDidDisappear();
	
	procTriggerEvent(DID_DISAPPEAR);
	CompositionRunner::defaultRunner().unregisterComposition(this);
}

inline void Composition::updateState()
{
	if (state == STARTED && alpha_delta > 0.)
	{
		state = FADEIN;
		
		_viewWillAppear();
	}
	if (state == FADEIN && alpha >= 1.)
	{
		alpha = 1;
		alpha_delta = 0;
		state = PLAYING;
		
		_viewDidAppear();
	}
	if (state == PLAYING && alpha_delta < 0.)
	{
		state = FADEOUT;
		
		_viewWillDisappear();
	}
	if (state == FADEOUT && alpha <= 0.)
	{
		alpha = 0;
		alpha_delta = 0;
		state = FINISHED;
		
		_viewDidDisappear();
	}
}

inline void Composition::procTimeEvent(float t0, float t1)
{
	multimap<float, Composition::Ref>::iterator begin = time_event_map.lower_bound(t0);
	multimap<float, Composition::Ref>::iterator end = time_event_map.upper_bound(t1);
	
	if (begin == end) return;
	
	multimap<float, Composition::Ref>::iterator it = begin;
	
	while (it != end)
	{
		Composition::Ref &o = it->second;
		o->play();
		it++;
	}
}

inline void Composition::procTriggerEvent(Trigger trigger)
{
	if (trigger_event_map.count(trigger))
	{
		std::pair<multimap<Trigger, Composition::Ref>::iterator,
		multimap<Trigger, Composition::Ref>::iterator> range = trigger_event_map.equal_range(trigger);
		multimap<Trigger, Composition::Ref>::iterator it = range.first;
		while (it != range.second)
		{
			Composition::Ref &o = it->second;
			o->play();
			it++;
		}
		
		ofNotifyEvent(onTrigger, trigger, this);
	}
}

inline Composition::Ref Composition::on(Trigger event, Composition::Ref o, Duration s)
{
	if (o.get() == this)
	{
		throw;
	}
	
	trigger_event_map.insert(make_pair(event, o));
	o->duration = s;
	
	return o;
}

inline Composition::Ref Composition::at(float time, Composition::Ref o, Duration s)
{
	if (o.get() == this)
	{
		throw;
	}
	
	time_event_map.insert(make_pair(time, o));
	o->duration = s;
	
	return o;
}

#pragma mark - CompositionRunner

