<h1>Documentation</h1>

<h2>Physics:</h2>

<p>Located by path source/engine/physics/ <br>
in this folder you can find Collider and enum file EPhisicsType (with EResponseType and EObjectTypes) <br>

PhysicsManager is located by path source/engine/managers/ </p>


  <h4>Collider includes:</h4>
  <ul>
    <li> Overlap Delegate </li>
</ul>
    <h5>Variables: </h5>
<ul>
	<li> std::map<EObjectTypes, EResponseType> Map of response to objects </li>
    <li> glm::vec2 Size </li>
    <li> glm::vec2 World position </li>
    <li>EObjectTypes Object type </li>
	</ul>
    <h5> Methods: </h5>
    <ul>
    <li> void AddOverlapDelegate(Object, method by reference) </li>
    <li> void Overlap(Actor*) </li>
    <li> void SetObjectType(EObjectTypes) </li>
    <li> void SetSize(glm::vec2) </li>
    <li> void SetPosition(glm::vec2) </li>
    <li> void SetCollisionResponse(EObjectTypes, EResponseType) </li>
    <li> Actor* GetOwner() </li>
    <li> glm::vec2 GetSize() </li>
    <li> glm::vec2 GetPosition() </li>
    <li> EObjectTypes GetObjectType() </li>
    <li> EResponseType GetResponseType(EObjectTypes) </li>
</ul>
	<h5> Constructors: </h5>
	<ul>
	<li>- Collider(EOdjectTypes, glm::vec2(position), glm::vec2(size)) </li>
	</ul>
  <h4>PhysicsManager includes: </h4>
    <h5>Methods: </h5>
    <ul>
	<li> static bool CanMove(Actor* actor_that_need_to_check, glm::vec2(next_position)) </li>
     <li> static void CheckOverlapping(Collider* check_collider) </li>
     <li> static bool IsOverlap(glm::vec2 position, glm::vec2 check_position,  
    glm::vec2 size, glm::vec3 size_checking_colllider, 
    Physics::Collider* check_collider, Physics::Collider* current_checking_collider) </li>
     <li> static bool IsBlocking(glm::vec2 position, glm::vec2 check_position, 
		glm::vec2 size, glm::vec2 size_checking_colllider, 
		Physics::Collider* check_collider, Physics::Collider* current_checking_collider) </li>
    </ul>
<h2> Renderer: </h2>
  <p> Located by path source/engine/renderer/ </p>
  
  <h4> Sprite includes: </h4>
    <h5> Variables: </h5>
    <ul>
	<li> std::shared_ptr<Texture2D> spr_texture </li>
	<li> std::shared_ptr<ShaderProgram> spr_shader </li>
	<li> glm::vec2 spr_pos, spr_size </li>
	<li> float spr_rot </li>
	<li> std::string spr_subtexture_name </li>
	<li> GLuint spr_vertex_array_objects, texture_coord_buffer, vertex_coord_buffer, vertex_element_buffer </li>
	</ul>
    <h5> Methods: </h5>
    <ul>
	<li> Sprite& operator=(Sprite) = delete </li>
	<li> void SetPosition(glm::vec2 newPosition) </li>
	<li> void SetSize(glm::vec2 newSize) </li>
	<li> void SetRotation(float newRotation) </li>
	<li> void SetNewSprite(std::string newSubtextureName) </li>
	<li> glm::vec2 GetPosition() </li>
	<li> glm::vec2 GetSize() </li>
	<li> float GetRotation() </li>
	<li> std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram() </li>
	<li> std::shared_ptr<Renderer::Texture2D> GetTexture() </li>
     	<li> virtual void Render() </li>
    </ul>
    <h5> Constructors: </h5>
    <ul>
	<li> Sprite(std::shared_ptr<Texture2D> texture, std::shared_ptr <ShaderProgram> shader, 
			std::string initialSubtextureName, glm::vec2 position, 
		glm::vec2 size, float rotation) </li>
		<li> Sprite(Sprite) = delete </li>
	</ul>
		<h4> AnimSprite inherited from Sprite includes: </h4>
	<h5> Variables: </h5>
		<ul>
			<li> size_t current_frame </li>
     <li> float current_anim_time </li>
     <li> bool is_dirty </li>
     <li> std::map<std::string, std::vector<std::pair<std::string, float>>> states_map </li>
     <li> std::map<std::string, std::vector<std::pair<std::string, float>>>::const_iterator current_anim_duration </li>
			</ul>
		<h5> Inherited members: </h5>
    <ul>
	<li> std::shared_ptr<Texture2D> spr_texture </li>
	<li> std::shared_ptr<ShaderProgram> spr_shader </li>
	<li> glm::vec2 spr_pos, spr_size </li>
	<li> float spr_rot </li>
	<li> std::string spr_subtexture_name </li>
	<li> GLuint spr_vertex_array_objects, texture_coord_buffer, vertex_coord_buffer, vertex_element_buffer </li>
	</ul>
		<h5> Methods: </h5>
		<ul>
     <li> void InsertState(std::string name_state, std::vector<std::pair<std::string, float>> sub_texture_duration) </li>
     <li> void SetState(std::string name_state) </li>
     <li> void Update(float deltaTime) </li>
		</ul>
		<h5> Inherited methods: </h5>
		<ul>
			<li> void Render() </li>
		</ul>
