## Ray-sphere intersection (the quadratic + discriminant)

A point is on the sphere when its distance from the center equals the radius.
Plugging the ray P(t) = origin + t·dir into that equation and expanding gives a
quadratic in t, which is the `a`, `h`, `c` setup in `sphere::hit`. The
discriminant (h·h - a·c) is the key: negative means the ray misses entirely,
zero grazes the edge, positive means it punches through at two values of t. When
it's positive I take the smaller root first (the nearer hit), and only fall back
to the far one if the near one is outside the allowed range.

## Surface normals (why (P−C)/r, and front-face vs back-face)

The normal is the direction pointing straight out of the surface, which I need
for shading and for bouncing rays. On a sphere that's just the hit point minus
the center, and dividing by the radius makes it length 1 for free instead of
calling normalize. The front-face vs back-face thing matters because a ray can
hit a sphere from outside or from inside (e.g. glass later) - `set_face_normal`
checks the dot product of the ray and the outward normal and flips the normal so
it always faces back against the incoming ray.

## The hittable abstraction (why an abstract base class for objects)

`hittable` is just a contract: anything in the scene has to provide a `hit()`
function that says whether a given ray strikes it. Making it an abstract base
class means the renderer never has to know what it's actually looking at - it
calls `hit()` and that's it. Right now the only thing implementing it is
`sphere`, but `hittable_list` implements it too, and later shapes will plug in
the same way without touching the camera code.

## hit_record (what info a hit needs to carry forward, and why)

When a ray hits something, one bool isn't enough — the shading code needs the
details. So `hit_record` is the little struct that gets filled in: the point `p`
where it hit, the `normal` there, the distance `t`, whether it was a front face,
and a pointer to the `mat` (material) that was hit. That last one is what lets
the camera ask the surface how to scatter the ray without knowing or caring what
material it is.

## Antialiasing (why multiple random samples per pixel, then average)

A pixel covers a tiny square of the image, not a single point, so shooting one
ray dead-center gives hard, jagged edges. Instead I fire `samples_per_pixel`
rays, each jittered to a random spot inside the pixel (`sample_square` in the
camera), and average the colors. Edges end up as a blend of what's behind and in
front of them, which is what makes them look smooth instead of stair-stepped.

## The material abstraction (why materials own the "scatter" behavior)

Instead of the camera hard-coding how light behaves, each material owns its own
`scatter()` function. The camera just hits a surface, grabs its material off the
`hit_record`, and checks the given ray and how much light it reflets - that's the 
scattered ray plus the attenuation color. This keeps the renderer dumb and lets 
me add new surface types (matte, metal, glass...) by writing a new material,
not by editing the camera.

## Diffuse/Lambertian scattering (random direction, why)

A matte surface scatters light in lots of directions, so the bounced ray
shouldn't be predictable. The trick is to take the normal and add a random unit
vector to it, which biases the new direction toward the normal but still spreads
it around - that bias is what gives the realistic Lambertian look. There's also
a guard for when the random vector almost exactly cancels the normal (`near_zero`),
since that would leave a zero-length direction and break later math.

## Metal reflection 

Metal is a mirror, so the bounce isn't random — it reflects. The incoming ray v
can be split into the part along the normal and the part across it; to reflect,
I keep the across part and flip the along part. dot(v, n) is how far v goes into
the surface along the normal, so n·dot(v,n) is that component, and subtracting it
twice (v − 2·dot(v,n)·n) flips it to point back out. That's exactly what
`reflect()` does, and `metal::scatter` just feeds the result out as the new ray.
