# Documentation

## Physics:

Located by path source/engine/physics/  
in this folder you can find Collider and enum file EPhisicsType (with EResponseType and EObjectTypes)

PhysicsManager is located by path source/engine/managers/ 

### Collider includes:

* Overlap Delegate

#### Variables: 

* std::map<EObjectTypes, EResponseType> Map of response to objects 
* glm::vec2 Size 
* glm::vec2 World position 
* EObjectTypes Object type 

#### Methods: 

* void AddOverlapDelegate(Object, method by reference) 
* void Overlap(Actor*) 
* void SetObjectType(EObjectTypes) 
* SetSize(glm::vec2) 
* void SetPosition(glm::vec2) 
* void SetCollisionResponse(EObjectTypes, EResponseType) 
* Actor* GetOwner() 
* glm::vec2 GetSize()
* glm::vec2 GetPosition() 
* EObjectTypes GetObjectType() 
* EResponseType GetResponseType(EObjectTypes)

### Constructors: 

* Collider(EOdjectTypes, glm::vec2(position), glm::vec2(size))

### PhysicsManager includes: 
#### Methods: 

* static bool CanMove(Actor* actor_that_need_to_check, glm::vec2(next_position))
* static void CheckOverlapping(Collider* check_collider)
* static bool IsOverlap(glm::vec2 position, glm::vec2 check_position, glm::vec2 size, glm::vec3 size_checking_colllider, Physics::Collider*  
check_collider, Physics::Collider* current_checking_collider) 
* static bool IsBlocking(glm::vec2 position, glm::vec2 check_position, glm::vec2 size, glm::vec2 size_checking_colllider, Physics::Collider*   
check_collider, Physics::Collider* current_checking_collider) 

### Renderer:
  
Located by path source/engine/renderer/
  
### Sprite includes: 

#### Variables: 

* std::shared_ptr<Texture2D> spr_texture 
* std::shared_ptr<ShaderProgram> spr_shader 
* glm::vec2 spr_pos, spr_size 
* float spr_rot 
* std::string spr_subtexture_name 
* GLuint spr_vertex_array_objects, texture_coord_buffer, vertex_coord_buffer, vertex_element_buffer


#### Methods:

* Sprite& operator=(Sprite) = delete 
* void SetPosition(glm::vec2 newPosition) 
* void SetSize(glm::vec2 newSize) 
* void SetRotation(float newRotation) 
* void SetNewSprite(std::string newSubtextureName) 
* glm::vec2 GetPosition() 
* glm::vec2 GetSize() 
* float GetRotation() 
* std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram() 
* std::shared_ptr<Renderer::Texture2D> GetTexture() 
* virtual void Render() 

#### Constructors:

* Sprite(std::shared_ptr<Texture2D> texture, std::shared_ptr <ShaderProgram> shader, std::string initialSubtextureName, glm::vec2 position, ::vec2 size, float rotation)
* Sprite(Sprite) = delete 

### AnimSprite inherited from Sprite includes: 
 
#### Variables: 

    
* size_t current_frame 
* float current_anim_time 
* bool is_dirty 
* std::map<std::string, std::vector<std::pair<std::string, float>>> states_map 
* std::map<std::string, std::vector<std::pair<std::string, float>>>::const_iterator current_anim_duration 
			
#### Inherited members:
    
* std::shared_ptr<Texture2D> spr_texture 
* std::shared_ptr<ShaderProgram> spr_shader 
* glm::vec2 spr_pos, spr_size 
* float spr_rot 
* std::string spr_subtexture_name 
* GLuint spr_vertex_array_objects, texture_coord_buffer, vertex_coord_buffer, vertex_element_buffer 
	
#### Methods:
		
* void InsertState(std::string name_state, std::vector<std::pair<std::string, float>> sub_texture_duration) 
* void SetState(std::string name_state) 
* void Update(float deltaTime) 
		
#### Inherited methods: 
		
* void Render() 
		
