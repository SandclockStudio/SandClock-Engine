#include "ComponentParticle.h"

#include "ComponentCamera.h"

ComponentParticle::ComponentParticle()
{
}

ComponentParticle::~ComponentParticle()
{
}

void ComponentParticle::Init(unsigned max_particles, const char* file)
{
	//accum_elapsed = max_particles;
	accum_elapsed = 5000;
	texture = loadImages(file);
	Particle p = Particle();
	p.position = float3(1, 10, -4);
	p.velocity = float3(0, -0.1f, 0);
	particles.push_back(p);

}

bool ComponentParticle::Update(Frustum f)
{
	for (size_t i = 0; i < particles.size(); i++) 
	{
		particles[i].position += particles[i].velocity * 0.5f;
		particles[i].lifetime += 0.5f;

		alive.clear();
		dead.clear();

		if (particles[i].lifetime >= accum_elapsed )
		{
			dead.push_back(i);
		}
		else
			alive.push_back(i);
			
	}

	ComputeQuad(f);
	Draw();


	return true;
}

bool ComponentParticle::Draw()
{
	for (size_t  i = 0; i < alive.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_TRIANGLES);
		glTexCoord2d(0.0, 0.0);
		glVertex3f(particles[alive[i]].positions[3].x, particles[alive[i]].positions[3].y, particles[alive[i]].positions[3].z);
		glTexCoord2d(1.0, 0.0);
		glVertex3f(particles[alive[i]].positions[1].x, particles[alive[i]].positions[1].y, particles[alive[i]].positions[1].z);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(particles[alive[i]].positions[0].x, particles[alive[i]].positions[0].y, particles[alive[i]].positions[0].z);

		glTexCoord2d(0.0, 0.0);
		glVertex3f(particles[alive[i]].positions[3].x, particles[alive[i]].positions[3].y, particles[alive[i]].positions[3].z);
		glTexCoord2d(1.0, 1.0);
		glVertex3f(particles[alive[i]].positions[0].x, particles[alive[i]].positions[0].y, particles[alive[i]].positions[0].z);
		glTexCoord2d(0.0, 1.0);
		glVertex3f(particles[alive[i]].positions[2].x, particles[alive[i]].positions[2].y, particles[alive[i]].positions[2].z);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	

	return true;
}

void ComponentParticle::ComputeQuad(Frustum f)
{
	for (size_t i = 0; i < alive.size(); i++)
	{
		Particle* p = &particles[alive[i]];
		
		p->normal = (f.Pos() - p->position);
		p->up = float3(0, 1, 0);

		p->right = p->normal.Cross(p->up);

		p->right.Normalize();

		p->positions[0] = p->position + p->up + p->right;
		p->positions[1] = p->position - p->up + p->right;
		p->positions[2] = p->position + p->up - p->right;
		p->positions[3] = p->position - p->up - p->right;
	}
}


// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
GLuint ComponentParticle::loadImages(const char* theFileName)
{
	ILuint imageId;
	ilGenImages(1, &imageId);
	ilBindImage(imageId);

	if (ilLoadImage(theFileName))
	{
		GLuint textureId = 0;
		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}


		int components = 3;
		int format = GL_RGB;

		switch (ilGetInteger(IL_IMAGE_FORMAT))
		{
		case IL_RGB:
			components = 3;
			format = GL_RGB;
			break;
		case IL_RGBA:
			components = 4;
			format = GL_RGBA;
			break;
		case IL_BGR:
			components = 3;
			format = GL_BGR_EXT;
			break;
		case IL_BGRA:
			components = 4;
			format = GL_BGRA_EXT;
			break;
		default:
			break;
		}

		ILubyte* data = ilGetData();
		int width = ilGetInteger(IL_IMAGE_WIDTH);
		int height = ilGetInteger(IL_IMAGE_HEIGHT);
		int channels = ilGetInteger(IL_IMAGE_CHANNELS);

		if (channels == 3)
			ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		else if (channels == 4)
			ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		glTexImage2D(GL_TEXTURE_2D, 0, components, width,
			height, 0, format,
			GL_UNSIGNED_BYTE, data);

		ilDeleteImages(1, &imageId);

		glBindTexture(GL_TEXTURE_2D, 0);

		return textureId;
	}

	return 0;
}