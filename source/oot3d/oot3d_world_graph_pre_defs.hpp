/*===============================================
|              LOGIC DEFINITIONS                |
================================================*/
#define CHILD_DAY                   logic->ageTime & 0b0001 && true
#define CHILD_NIGHT                 logic->ageTime & 0b0010 && true
#define ADULT_DAY                   logic->ageTime & 0b0100 && true
#define ADULT_NIGHT                 logic->ageTime & 0b1000 && true
#define IS_CHILD                    CHILD_DAY || CHILD_NIGHT
#define IS_ADULT                    ADULT_DAY || ADULT_NIGHT
#define AT_DAY                      CHILD_DAY || ADULT_DAY
#define AT_NIGHT                    CHILD_NIGHT || ADULT_NIGHT

#define HOOKSHOT                    logic->items.progressiveHookshot >= 1
#define LONGSHOT                    logic->items.progressiveHookshot >= 2
#define GORON_BRACELET              logic->items.progressiveStrengthUpgrade >= 1
#define SILVER_GAUNTLETS            logic->items.progressiveStrengthUpgrade >= 2
#define GOLDEN_GAUNTLETS            logic->items.progressiveStrengthUpgrade >= 3
#define SCARECROW                   logic->items.progressiveHookshot >= 1 && logic->items.scarecrowSong
#define DISTANT_SCARECROW           logic->items.progressiveHookshot >= 2 && logic->items.scarecrowSong
#define SILVER_SCALE                logic->items.progressiveScale >= 1
#define GOLD_SCALE                  logic->items.progressiveScale >= 2
#define OCARINA                     logic->items.progressiveOcarina >= 1
#define OCARINA_OF_TIME             logic->items.progressiveOcarina >= 2
#define ADULTS_WALLET               logic->items.progressiveWallet >= 1
#define GIANTS_WALLET               logic->items.progressiveWallet >= 2

#define KOKIRI_EMERALD              logic->items.kokiriEmerald && true
#define GORON_RUBY                  logic->items.goronRuby && true
#define ZORA_SAPPHIRE               logic->items.zoraSapphire && true
#define FOREST_MEDALLION            logic->items.forestMedallion && true
#define FIRE_MEDALLION              logic->items.fireMedallion && true
#define WATER_MEDALLION             logic->items.waterMedallion && true
#define SPIRIT_MEDALLION            logic->items.spiritMedallion && true
#define SHADOW_MEDALLION            logic->items.shadowMedallion && true
#define LIGHT_MEDALLION             logic->items.lightMedallion && true

#define DEKU_TREE_CLEAR             logic->items.dekuTreeClear && true
#define DODONGOS_CAVERN_CLEAR       logic->items.dodongosCavernClear && true
#define JABU_JABUS_BELLY_CLEAR      logic->items.jabuJabusBellyClear && true
#define FOREST_TEMPLE_CLEAR         logic->items.forestMedallion && true
#define FIRE_TEMPLE_CLEAR           logic->items.fireMedallion && true
#define WATER_TEMPLE_CLEAR          logic->items.waterMedallion && true
#define SPIRIT_TEMPLE_CLEAR         logic->items.spiritMedallion && true
#define SHADOW_TEMPLE_CLEAR         logic->items.shadowMedallion && true

#define GORON_TUNIC                 logic->items.goronTunic || logic->items.buyGoronTunic
#define ZORA_TUNIC                  logic->items.zoraTunic || logic->items.buyZoraTunic

#define BOW                         logic->items.progressiveBow && true
#define BOMBS                       logic->items.progressiveBombBag && true
#define MAGIC_METER                 logic->items.progressiveMagicMeter && true
#define DEKU_SHIELD                 logic->items.buyDekuShield && true
#define HYLIAN_SHIELD               logic->items.buyHylianShield && true
#define MIRROR_SHIELD               logic->items.mirrorShield && true
#define NUTS                        logic->items.buyDekuNut5 || logic->items.buyDekuNut10 || logic->items.dekuNutDrop
#define STICKS                      logic->items.buyDekuStick1 || logic->items.dekuStickDrop
#define BUGS                        logic->items.bugs || logic->items.buyBottleBug
#define BLUE_FIRE                   logic->items.blueFire || logic->items.buyBlueFire
#define FISH                        logic->items.fish || logic->items.buyFish
#define FAIRY                       logic->items.fairy || logic->items.buyFairysSpirit
#define MAGIC_BEAN                  logic->items.magicBean && true
#define MAGIC_BEAN_PACK             logic->items.magicBeanPack && true
#define GOLD_SKULLTULA_TOKENS       logic->items.goldSkulltulaToken
#define GERUDO_TOKEN                logic->items.gerudoToken && true
#define DOUBLE_DEFENSE              logic->items.doubleDefense && true

#define WEIRD_EGG                   logic->items.weirdEgg && true
#define CUCCO                       logic->items.cucco && true
#define ZELDAS_LETTER               logic->items.zeldasLetter && true
#define KEATON_MASK                 logic->items.keatonMask && true
#define SKULL_MASK                  logic->items.skullMask && true
#define SPOOKY_MASK                 logic->items.spookyMask && true
#define BUNNY_HOOD                  logic->items.bunnyHood && true
#define GORON_MASK                  logic->items.goronMask && true
#define ZORA_MASK                   logic->items.zoraMask && true
#define GERUDO_MASK                 logic->items.gerudoMask && true
#define MASK_OF_TRUTH               logic->items.maskOfTruth && true
#define POCKET_EGG                  logic->items.pocketEgg && true
#define POCKET_CUCCO                logic->items.pocketCucco && true
#define COJIRO                      logic->items.cojiro && true
#define ODD_MUSHROOM                logic->items.oddMushroom && true
#define ODD_POULTICE                logic->items.oddPoultice && true
#define POACHERS_SAW                logic->items.poachersSaw && true
#define BROKEN_GORONS_SWORD         logic->items.brokenGoronsSword && true
#define PRESCRIPTION                logic->items.prescription && true
#define EYEBALL_FROG                logic->items.eyeballFrog && true
#define EYEDROPS                    logic->items.eyedrops && true
#define CLAIM_CHECK                 logic->items.claimCheck && true

#define LINKS_COW                   logic->items.linksCow && true
#define EPONA                       logic->items.epona && true
#define SHARD_OF_AGONY              logic->items.shardOfAgony && true
#define KOKIRI_SWORD                logic->items.kokiriSword && true && true
#define MASTER_SWORD                logic->items.masterSword && true
#define BIGGORON_SWORD              logic->items.biggoronsSword && true
#define SLINGSHOT                   logic->items.progressiveSlingshot && true
#define BOOMERANG                   logic->items.boomerang && true
#define DINS_FIRE                   logic->items.dinsFire && true
#define FARORES_WIND                logic->items.faroresWind && true
#define NAYRUS_LOVE                 logic->items.nayrusLove && true
#define LENS_OF_TRUTH               logic->items.lensOfTruth && true
#define MEGATON_HAMMER              logic->items.megatonHammer && true
#define IRON_BOOTS                  logic->items.ironBoots && true
#define HOVER_BOOTS                 logic->items.hoverBoots && true
#define FIRE_ARROWS                 logic->items.fireArrows && true
#define ICE_ARROWS                  logic->items.iceArrows && true
#define LIGHT_ARROWS                logic->items.lightArrows && true

#define FOUND_BOMBCHUS             (logic->settings.bombchusInLogic && (logic->items.progressiveBombchus || logic->items.bombchus5 || logic->items.bombchus10 || logic->items.bombchus20)) || (!logic->settings.bombchusInLogic && BOMBS)
#define CAN_REFILL_BOMBCHUS         logic->items.buyBombchu5 || logic->items.buyBombchu10 || logic->items.buyBombchu20 || logic->items.bombchuDrop || (logic->settings.ammoDrops == AMMODROPS_BOMBCHU && FOUND_BOMBCHUS)
#define HAS_BOMBCHUS               (logic->settings.bombchusInLogic && FOUND_BOMBCHUS) || (!logic->settings.bombchusInLogic && CAN_REFILL_BOMBCHUS)
#define HAS_EXPLOSIVES              BOMBS || (logic->settings.bombchusInLogic && HAS_BOMBCHUS)
#define HAS_BOTTLE                  logic->items.emptyBottle && true
#define RUTOS_LETTER                logic->items.rutosLetter && true

#define ZELDAS_LULLABY              logic->items.zeldasLullaby && true
#define SARIAS_SONG                 logic->items.sariasSong && true
#define SUNS_SONG                   logic->items.sunsSong && true
#define SONG_OF_STORMS              logic->items.songOfStorms && true
#define SONG_OF_TIME                logic->items.songOfTime && true
#define EPONAS_SONG                 logic->items.eponasSong && true
#define MINUET_OF_FOREST            logic->items.minuetOfForest && true
#define BOLERO_OF_FIRE              logic->items.boleroOfFire && true
#define SERENADE_OF_WATER           logic->items.serenadeOfWater && true
#define REQUIEM_OF_SPIRIT           logic->items.requiemOfSpirit && true
#define NOCTURNE_OF_SHADOW          logic->items.nocturneOfShadow && true
#define PRELUDE_OF_LIGHT            logic->items.preludeOfLight && true

#define CAN_PLAY_ZELDAS_LULLABY     OCARINA && ZELDAS_LULLABY
#define CAN_PLAY_SARIAS_SONG        OCARINA && SARIAS_SONG
#define CAN_PLAY_SUNS_SONG          OCARINA && SUNS_SONG
#define CAN_PLAY_SONG_OF_STORMS     OCARINA && SONG_OF_STORMS
#define CAN_PLAY_SONG_OF_TIME       OCARINA && SONG_OF_TIME
#define CAN_PLAY_EPONAS_SONG        OCARINA && EPONAS_SONG
#define CAN_PLAY_MINUET_OF_FOREST   OCARINA && MINUET_OF_FOREST
#define CAN_PLAY_BOLERO_OF_FIRE     OCARINA && BOLERO_OF_FIRE
#define CAN_PLAY_SERENADE_OF_WATER  OCARINA && SERENADE_OF_WATER
#define CAN_PLAY_REQUIEM_OF_SPIRIT  OCARINA && REQUIEM_OF_SPIRIT
#define CAN_PLAY_NOCTURNE_OF_SHADOW OCARINA && NOCTURNE_OF_SHADOW
#define CAN_PLAY_PRELUDE_OF_LIGHT   OCARINA && PRELUDE_OF_LIGHT

#define CAN_USE_KOKIRI_SWORD        IS_CHILD && KOKIRI_SWORD
#define CAN_USE_MASTER_SWORD        IS_ADULT && MASTER_SWORD
#define CAN_USE_BIGGORON_SWORD      IS_ADULT && BIGGORON_SWORD
#define CAN_USE_STICKS              IS_CHILD && STICKS
#define CAN_USE_SLINGSHOT           IS_CHILD && SLINGSHOT
#define CAN_USE_BOOMERANG           IS_CHILD && BOOMERANG
#define CAN_USE_DEKU_SHIELD         IS_CHILD && DEKU_SHIELD
#define CAN_USE_DINS_FIRE           MAGIC_METER && DINS_FIRE
#define CAN_USE_FARORES_WIND        MAGIC_METER && FARORES_WIND
#define CAN_USE_NAYRUS_LOVE         MAGIC_METER && NAYRUS_LOVE
#define CAN_USE_LENS_OF_TRUTH       MAGIC_METER && LENS_OF_TRUTH
#define CAN_USE_BOW                 IS_ADULT && BOW
#define CAN_USE_MEGATON_HAMMER      IS_ADULT && MEGATON_HAMMER
#define CAN_USE_IRON_BOOTS          IS_ADULT && IRON_BOOTS
#define CAN_USE_HOVER_BOOTS         IS_ADULT && HOVER_BOOTS
#define CAN_USE_HOOKSHOT            IS_ADULT && HOOKSHOT
#define CAN_USE_LONGSHOT            IS_ADULT && LONGSHOT
#define CAN_USE_SILVER_GAUNTLETS    IS_ADULT && SILVER_GAUNTLETS
#define CAN_USE_GOLDEN_GAUNTLETS    IS_ADULT && GOLDEN_GAUNTLETS
#define CAN_USE_GORON_TUNIC         IS_ADULT && GORON_TUNIC
#define CAN_USE_ZORA_TUNIC          IS_ADULT && ZORA_TUNIC
#define CAN_USE_SCARECROW           IS_ADULT && SCARECROW
#define CAN_USE_DISTANT_SCARECROW   IS_ADULT && DISTANT_SCARECROW
#define CAN_USE_MIRROR_SHIELD       IS_ADULT && MIRROR_SHIELD
#define CAN_USE_FIRE_ARROWS         IS_ADULT && FIRE_ARROWS && BOW && MAGIC_METER
#define CAN_USE_ICE_ARROWS          IS_ADULT && ICE_ARROWS && BOW && MAGIC_METER
#define CAN_USE_LIGHT_ARROWS        IS_ADULT && LIGHT_ARROWS && BOW && MAGIC_METER

#define FOREST_TEMPLE_SMALL_KEYS          logic->items.forestTempleSmallKey
#define FIRE_TEMPLE_SMALL_KEYS            logic->items.fireTempleSmallKey
#define WATER_TEMPLE_SMALL_KEYS           logic->items.waterTempleSmallKey
#define SPIRIT_TEMPLE_SMALL_KEYS          logic->items.spiritTempleSmallKey
#define SHADOW_TEMPLE_SMALL_KEYS          logic->items.shadowTempleSmallKey
#define BOTTOM_OF_THE_WELL_SMALL_KEYS     logic->items.bottomOfTheWellSmallKey
#define GERUDO_TRAINING_GROUND_SMALL_KEYS logic->items.gerudoTrainingGroundSmallKey
#define THIEVES_HIDEOUT_SMALL_KEYS        logic->items.thievesHideoutSmallKey
#define GANONS_CASTLE_SMALL_KEYS          logic->items.ganonsCastleSmallKey
#define CHEST_GAME_SMALL_KEYS             logic->items.chestGameSmallKey

#define HAS_SHIELD                          (IS_CHILD && DEKU_SHIELD) || (IS_ADULT && HYLIAN_SHIELD)
#define CAN_SHIELD                          (IS_CHILD && DEKU_SHIELD) || (IS_ADULT && (HYLIAN_SHIELD || MIRROR_SHIELD))
#define CAN_JUMPSLASH                        IS_ADULT || STICKS || KOKIRI_SWORD
#define CAN_BLAST_OR_SMASH                   HAS_EXPLOSIVES || MEGATON_HAMMER
#define CAN_CHILD_ATTACK                     IS_CHILD && (SLINGSHOT || BOOMERANG || STICKS || KOKIRI_SWORD || HAS_EXPLOSIVES || DINS_FIRE)
#define CAN_CHILD_DAMAGE                     IS_CHILD && (SLINGSHOT              || STICKS || KOKIRI_SWORD || HAS_EXPLOSIVES || DINS_FIRE)
#define CAN_CUT_SHRUBS                       IS_ADULT || STICKS || KOKIRI_SWORD || BOOMERANG || HAS_EXPLOSIVES
#define CAN_LEAVE_FOREST                     logic->settings.openForest != OPENFOREST_OPEN || IS_ADULT || logic->items.dekuTreeClear
#define CAN_PLANT_BUGS                       IS_CHILD && BUGS
#define CAN_RIDE_EPONA                       IS_ADULT && EPONA && CAN_PLAY_EPONAS_SONG
#define CAN_STUN_DEKU                        IS_ADULT || (SLINGSHOT || BOOMERANG || STICKS || KOKIRI_SWORD || HAS_EXPLOSIVES || DINS_FIRE || NUTS || DEKU_SHIELD)
#define CAN_SUMMON_GOSSIP_FAIRY              OCARINA && (ZELDAS_LULLABY || EPONAS_SONG || SONG_OF_TIME || SUNS_SONG)
#define CAN_SUMMON_GOSSIP_FAIRY_WITHOUT_SUNS OCARINA && (ZELDAS_LULLABY || EPONAS_SONG || SONG_OF_TIME)
#define HEARTS                               logic->settings.baseHearts + logic->items.heartContainer + (logic->items.pieceOfHeart >> 2)
#define MULTIPLIER                           (logic->settings.damageMultiplier < 6) ? logic->settings.damageMultiplier : 10
#define EFFECTIVE_HEALTH                     ((HEARTS << (2 + DOUBLE_DEFENSE)) >> MULTIPLIER) + ((HEARTS << (2 + DOUBLE_DEFENSE)) % (1 << MULTIPLIER) > 0)
#define FIRE_TIMER                           CAN_USE_GORON_TUNIC ? 255 : (logic->tricks.fewerTunicRequirements) ? (HEARTS * 8) : 0
#define WATER_TIMER                          CAN_USE_ZORA_TUNIC  ? 255 : (logic->tricks.fewerTunicRequirements) ? (HEARTS * 8) : 0
#define NEED_NAYRUS_LOVE                     EFFECTIVE_HEALTH == 1
#define CAN_SURVIVE_DAMAGE                   !NEED_NAYRUS_LOVE || CAN_USE_NAYRUS_LOVE
#define CAN_TAKE_DAMAGE                      FAIRY || CAN_SURVIVE_DAMAGE
#define CAN_TAKE_DAMAGE_TWICE                (FAIRY && HAS_BOTTLE >= 2) || ((EFFECTIVE_HEALTH == 2) && (CAN_USE_NAYRUS_LOVE || FAIRY)) || (EFFECTIVE_HEALTH > 2)
#define CAN_PLANT_BEAN                       logic->settings.plantBeans || (IS_CHILD && (MAGIC_BEAN || MAGIC_BEAN_PACK))

#define CAN_OPEN_BOMB_GROTTO        CAN_BLAST_OR_SMASH && (SHARD_OF_AGONY || logic->tricks.grottosWithoutAgony)
#define CAN_OPEN_STORM_GROTTO       CAN_PLAY_SONG_OF_STORMS && (SHARD_OF_AGONY || logic->tricks.grottosWithoutAgony)
#define CAN_USE_PROJECTILE          HAS_EXPLOSIVES || (IS_ADULT && (BOW || HOOKSHOT)) || (IS_CHILD && (SLINGSHOT || BOOMERANG))
#define CAN_GET_NIGHT_TIME_GS       CAN_PLAY_SUNS_SONG || !logic->settings.nightGsExpectSuns

#define HAS_PROJECTILE_CHILD        HAS_EXPLOSIVES || SLINGSHOT || BOOMERANG
#define HAS_PROJECTILE_ADULT        HAS_EXPLOSIVES || BOW || HOOKSHOT
#define HAS_PROJECTILE_BOTH         HAS_PROJECTILE_CHILD && HAS_PROJECTILE_ADULT
#define HAS_PROJECTILE_EITHER       HAS_PROJECTILE_CHILD || HAS_PROJECTILE_ADULT

// #define GUARANTEE_HINT (hints == mask && Mask_of_Truth) || (hints == agony && Shard_of_Agony) || (hints != mask && hints != agony)
#define HAS_FIRE_SOURCE             CAN_USE_DINS_FIRE || CAN_USE_FIRE_ARROWS
#define HAS_FIRE_SOURCE_WITH_TORCH  HAS_FIRE_SOURCE || CAN_USE_STICKS
#define CAN_FINISH_GERUDOFORTRESS  (logic->settings.gerudoFortress == GERUDOFORTRESS_NORMAL && THIEVES_HIDEOUT_SMALL_KEYS >= 4 && (IS_ADULT || KOKIRI_SWORD) && ((IS_ADULT && (BOW || HOOKSHOT || HOVER_BOOTS)) || GERUDO_TOKEN || logic->tricks.gerudoKitchen)) || (logic->settings.gerudoFortress == GERUDOFORTRESS_FAST && THIEVES_HIDEOUT_SMALL_KEYS >= 1 && (IS_ADULT || KOKIRI_SWORD)) || (logic->settings.gerudoFortress == GERUDOFORTRESS_OPEN)

#define HAS_ALL_STONES              KOKIRI_EMERALD && GORON_RUBY && ZORA_SAPPHIRE
#define HAS_ALL_MEDALLIONS          FOREST_MEDALLION && FIRE_MEDALLION && WATER_MEDALLION && SHADOW_MEDALLION && SPIRIT_MEDALLION && LIGHT_MEDALLION
#define STONE_COUNT                 KOKIRI_EMERALD + GORON_RUBY + ZORA_SAPPHIRE
#define MEDALLION_COUNT             FOREST_MEDALLION + FIRE_MEDALLION + WATER_MEDALLION + SHADOW_MEDALLION + SPIRIT_MEDALLION + LIGHT_MEDALLION
#define REWARD_COUNT                STONE_COUNT + MEDALLION_COUNT

#define CAN_BUILD_RAINBOW_BRIDGE   (logic->settings.bridge == RAINBOWBRIDGE_OPEN) || \
                                   (logic->settings.bridge == RAINBOWBRIDGE_VANILLA && SHADOW_MEDALLION && SPIRIT_MEDALLION && LIGHT_ARROWS) || \
                                   (logic->settings.bridge == RAINBOWBRIDGE_STONES && STONE_COUNT >= logic->settings.bridgeStones) || \
                                   (logic->settings.bridge == RAINBOWBRIDGE_MEDALLIONS && MEDALLION_COUNT >= logic->settings.bridgeMedallions) || \
                                   (logic->settings.bridge == RAINBOWBRIDGE_REWARDS && REWARD_COUNT >= logic->settings.bridgeRewards) || \
                                   (logic->settings.bridge == RAINBOWBRIDGE_TOKENS && GOLD_SKULLTULA_TOKENS >= logic->settings.bridgeTokens)
#define CAN_TRIGGER_LACS           (logic->settings.lacsCondition == LACSCONDITION_VANILLA && SHADOW_MEDALLION && SPIRIT_MEDALLION) || \
                                   (logic->settings.lacsCondition == LACSCONDITION_STONES && STONE_COUNT >= logic->settings.lacsStones) || \
                                   (logic->settings.lacsCondition == LACSCONDITION_MEDALLIONS && MEDALLION_COUNT >= logic->settings.lacsMedallions) || \
                                   (logic->settings.lacsCondition == LACSCONDITION_REWARDS && REWARD_COUNT >= logic->settings.lacsRewards) || \
                                   (logic->settings.lacsCondition == LACSCONDITION_TOKENS && GOLD_SKULLTULA_TOKENS >= logic->settings.lacsTokens)
// #define CAN_RECEIVE_GANON_BOSSKEY
//     (logic->settings.shuffleGanonBosskey == GANONSBOSSKEY_LACS_STONES && STONE_COUNT >= logic->settings.ganons) ||
//     (logic->settings.shuffleGanonBosskey == medallions && has_medallions(ganon_bosskey_medallions)) ||
//     (logic->settings.shuffleGanonBosskey == dungeons && has_dungeon_rewards(ganon_bosskey_rewards)) ||
//     (logic->settings.shuffleGanonBosskey == tokens && count(Gold_Skulltula_Token, ganon_bosskey_tokens)) ||
//     (logic->settings.shuffleGanonBosskey != stones && logic->settings.shuffleGanonBosskey != medallions
//       && logic->settings.shuffleGanonBosskey != dungeons && logic->settings.shuffleGanonBosskey != tokens)
// STOP SUBSTITUTING //
#define HERE(requirement)                    logic->Here([this]{return requirement;})
#define AT(areaId,requirement)              logic->At(areaId, [this]{return requirement;})
