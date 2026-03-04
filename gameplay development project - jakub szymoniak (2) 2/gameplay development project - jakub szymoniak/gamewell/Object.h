#pragma once
#include <vector>

// A basic object with simple 2D box collision. 
// There are two constructors - one for a static image (no animation) and one for a dynamic one. 
class ImageID;
class Object
{

public:
	// Constructor for Static Image
	// filepath - Image to load. Relative to the .exe location (or main location when debugging in visual studio)
	// x and y - Coordinates to draw at, range is from 0 to window width (x) or window height (y) 
	// width and height - the size in pixels to draw the image over
	// shouldDraw - Whether or not to render the Object
	Object(const char* filepath, int x, int y, int width, int height, bool shoulddraw);
	
	// Constructor for animated Image
	// filepath - Images to load. Relative to the .exe location (or main location when debugging in visual studio)
	// imageCount - Number of images in the animation
	// fps - animation frames rendered per second
	// x and y - Coordinates to draw at, range is from 0 to window width (x) or window height (y)
	// width and height - the size in pixels to draw the image over
	// shouldDraw - Whether or not to render the Object
	Object(const char* filepath[], int imageCount, int fps, int x, int y, int width, int height, bool shoulddraw);
	
	/// Default Constructor. This creates an empty object that you can replace later. 
	/// Realistically this should not be used, it exists for projects without any expectation of pointer use!
	//Object();

	/// Copy Constructor
	Object(const Object& other);

	// Destructor
	~Object();

	int getmove(int move, int dist);

	// Init for Static Image
	// filepath - Image to load. Relative to the .exe location (or main location when debugging in visual studio)
	// x and y - Coordinates to draw at, range is from 0 to window width (x) or window height (y)
	// width and height - the size in pixels to draw the image over
	// shouldDraw - Whether or not to render the Object
	void Init(const char* filepath, int x, int y, int width, int height, bool shoulddraw);

	// Init for animated Image
	// filepath - Images to load. Relative to the .exe location (or main location when debugging in visual studio)
	// imageCount - Number of images in the animation
	// fps - animation frames rendered per second
	// x and y - Coordinates to draw at, range is from 0 to window width (x) or window height (y)
	// width and height - the size in pixels to draw the image over
	// shouldDraw - Whether or not to render the Object
	void InitAnimated(const char* filepath[], int numImages, int fps, int x, int y, int width, int height, bool shoulddraw);

	// Sets the x and y coordinates 
	/// x - input for x
	/// y - input for y
	virtual void SetPosition(int x, int y);

	/// Scale in all dimensions. Relative to the centre of the Object
	/// percentOfOriginalSize - The modifier that the object should scale by. 1 is native scale
	virtual void SetUniformScale(float percentOfOriginalSize);

	/// Enable/Disable Rendering
	///draw - Whether or not to render the image
	virtual void SetShouldDraw(bool draw);

	/// Enable/Disable Physics
	/// collide - Whether or not to process collisions
	virtual void SetShouldCollide(bool collide);

	/// Gets the x and y and passes into reference variables
	/// x - output for x
	/// y - output for y
	virtual void GetPosition(float& x, float& y);

	/// Return true if we are drawing
	virtual bool GetShouldDraw() const;

	/// Return true if collision is enabled
	virtual bool GetShouldCollide() const;

	/// Update will control animating, updating, and rendering
	virtual void Update();

	/// Check to see if this object is colliding with the object passed in
	virtual bool IsOverlapping(const Object& other);

	float FindTargetDistance(float XPos, float YPos, float targetXPos, float targetYPos);
	std::vector<float> FindTargetDirection(float vctLength, float targetXPos, float targetYPos);

	
protected:

	/// Protected Default Constructor for use internally
	Object(int x, int y, bool shouldDraw);

	ImageID* m_imageIDs;
	std::vector<float> direction;

private:

	

	int m_x, m_y, m_w, m_h;
	bool m_shouldDraw, m_shouldCollide , m_deletable;

	int m_animIdx, m_numFrames;
	float m_animTimer, m_timerInterval, m_scale;

	void GetDimensions(int& x, int& y, int& w, int& h) const;

};