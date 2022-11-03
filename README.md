Documentation

Physics:

Located by path source/engine/physics/
in this folder you can find Collider and enum file EPhisicsType (with EResponseType and EObjectTypes)

PhysicsManager is located by path source/engine/managers/


  <p>Collider includes: </n>
    - Overlap Delegate </n>
    Variables: </n>
    - std::map<EObjectTypes, EResponseType> Map of response to objects </n>
    - glm::vec2 Size </n>
    - glm::vec2 World position </n>
    - EObjectTypes Object type </n>
    Methods: </n>
    - void AddOverlapDelegate(Object, method by reference) </n>
    - void Overlap(Actor*) </n>
    - void SetObjectType(EObjectTypes) </n>
    - void SetSize(glm::vec2) </n>
    - void SetPosition(glm::vec2) </n>
    - void SetCollisionResponse(EObjectTypes, EResponseType) </n>
    - Actor* GetOwner() </n>
    - glm::vec2 GetSize() </n> 
    - glm::vec2 GetPosition() </n>
    - EObjectTypes GetObjectType() </n>
    - EResponseType GetResponseType(EObjectTypes) </n>
    Constructors: </n>
    - Collider(EOdjectTypes, glm::vec2(position), glm::vec2(size)) </n>
  PhysicsManager includes: </n>
    Methods: </n>
    - static bool CanMove(Actor* actor_that_need_to_check, glm::vec2(next_position)) </n>
    - static void CheckOverlapping(Collider* check_collider) </n>
    - static bool IsOverlap(glm::vec2 position, glm::vec2 check_position,  </n>
    glm::vec2 size, glm::vec3 size_checking_colllider, </n>
    Physics::Collider* check_collider, Physics::Collider* current_checking_collider) </n>
    - static bool IsBlocking(glm::vec2 position, glm::vec2 check_position, </n>
		glm::vec2 size, glm::vec2 size_checking_colllider, </n>
		Physics::Collider* check_collider, Physics::Collider* current_checking_collider) </n>
    </p>
Renderer:
  Located by path source/engine/renderer/
  
  Sprite includes:
    Variables:
    - std::shared_ptr<Texture2D> spr_texture
		- std::shared_ptr<ShaderProgram> spr_shader
		- glm::vec2 spr_pos, spr_size
		- float spr_rot
		- std::string spr_subtexture_name
		- GLuint spr_vertex_array_objects, texture_coord_buffer, vertex_coord_buffer, vertex_element_buffer
    Methods:
		- Sprite& operator=(Sprite) = delete
		- void SetPosition(glm::vec2 newPosition)
		- void SetSize(glm::vec2 newSize)
		- void SetRotation(float newRotation)
		- void SetNewSprite(std::string newSubtextureName)
		- glm::vec2 GetPosition()
		- glm::vec2 GetSize()
		- float GetRotation()
		- std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram()
		- std::shared_ptr<Renderer::Texture2D> GetTexture()
    - virtual void Render()
    Constructors:
    - Sprite(std::shared_ptr<Texture2D> texture, std::shared_ptr <ShaderProgram> shader, 
			std::string initialSubtextureName, glm::vec2 position, 
			glm::vec2 size, float rotation)
    - Sprite(Sprite) = delete
    
  AnimSprite inherited from Sprite includes:
    Variables:
    - size_t current_frame
    - float current_anim_time 
    - bool is_dirty
    - std::map<std::string, std::vector<std::pair<std::string, float>>> states_map
    - std::map<std::string, std::vector<std::pair<std::string, float>>>::const_iterator current_anim_duration
    Inherited members:
    - std::shared_ptr<Texture2D> spr_texture
		- std::shared_ptr<ShaderProgram> spr_shader
		- glm::vec2 spr_pos, spr_size
		- float spr_rot
		- std::string spr_subtexture_name
		- GLuint spr_vertex_array_objects, texture_coord_buffer, vertex_coord_buffer, vertex_element_buffer
    Methods:
    - void InsertState(std::string name_state, std::vector<std::pair<std::string, float>> sub_texture_duration)
    - void SetState(std::string name_state)
    - void Update(float deltaTime)
    Inherited methods:
    - void Render()
